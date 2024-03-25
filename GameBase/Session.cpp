#include "pch.h"
#include "LogBase.h"
#include "Session.h"
#include "SocketUtils.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"

Session::Session() : m_recvBuffer(BUFFER_SIZE)
{
	DebugLog("[%s]", __FUNCTION__);
	m_socket = SocketUtils::CreateSocket();
}

Session::~Session()
{
	DebugLog("[%s]", __FUNCTION__);
	SocketUtils::Close(m_socket);
}

void Session::Send(shared_ptr<SendBuffer> sendBuffer)
{
	{
		DebugLog("[%s]", __FUNCTION__);
		lock_guard<recursive_mutex> _lock(m_lock);

		m_sendQueue.push(sendBuffer);

		if (m_sendRegistered.exchange(true) == false)
			m_sendRegistered = true;			
	}

	if (m_sendRegistered == true)
		RegisterSend();
}

bool Session::Connect()
{
	DebugLog("[%s]", __FUNCTION__);
	return RegisterConnect();
}

void Session::Disconnect(const wchar_t* cause)
{
	if (m_connected.exchange(false) == false)
		return;	

	DebugLog("[%s]", __FUNCTION__);

	OnDisconnected();
	GetService()->ReleaseSession(GetSessionRef());

	RegisterDisconnect();
}

HANDLE Session::GetHandle()
{
	return reinterpret_cast<HANDLE>(m_socket);
}

void Session::Dispatch(IocpEvent* iocpEvent, __int32 numOfBytes)
{
	//cout << "Session::Dispatch()" << endl;
	switch (iocpEvent->m_eventType)
	{
	case EventType::eCONNECT:
		ProcessConnect();
		break;
	case EventType::eDISCONNECT:
		ProcessDisconnect();
		break;
	case EventType::eRECV:
		ProcessRecv(numOfBytes);
		break;
	case EventType::eSEND:
		ProcessSend(numOfBytes);
		break;
	default:
		break;
	}
}

bool Session::RegisterConnect()
{
	DebugLog("[%s]", __FUNCTION__);
	if (IsConnected() == true)
		return false;

	if (GetService()->GetServiceType() != ServiceType::Client)
		return false;

	//서버 종료시 서버가 바인딩 하고 있는 소캣이 TIME_WAIT 상태의 소캣 주소를 재사용 하여,
	//빠른 재시작 가능, 일반적으로 시스템이 소캣을 TIME_WAIT 상태로 만들어 모든 패킷이 네트워크에서 소멸될 시간을 제공한다.
	if (SocketUtils::SetReuseAddress(m_socket, true) == false)
		return false;

	if (SocketUtils::SetTcpNoDelay(m_socket, true) == false)
		return false;

	if (SocketUtils::BindAnyAddress(m_socket, 0) == false)
		return false;

	m_connectEvent.Init();
	m_connectEvent.m_owner = shared_from_this();

	DWORD _numOfBytes = 0;
	SOCKADDR_IN m_sockAddr = GetService()->GetNetAddress().GetSockAddr();

	//https://learn.microsoft.com/ko-kr/windows/win32/api/mswsock/nc-mswsock-lpfn_connectex
	//BOOL LpfnConnectex(
	//	[in]           SOCKET s,					: 이전에 바인딩된 연결되지 않은 소켓
	//	[in]           const sockaddr * name,		: 연결할 주소를 지정하는 sockaddr 구조체
	//	[in]           int namelen,					: sockaddr 구조체의 길이(바이트)
	//	[in, optional] PVOID lpSendBuffer,			: 연결이 설정된 후 전송할 버퍼에 대한 포인터 [옵션]
	//	[in]           DWORD dwSendDataLength,		: lpSendBuffer 데이터의 길이(바이트)입니다 lpSendBuffer가 null 이면 무시
	//	[out]          LPDWORD lpdwBytesSent,		: lpSendBuffer 세팅 시, 함수 반환값이 성공일 경우 전송 된 바이트 수
	//	[in]           LPOVERLAPPED lpOverlapped	: 처리하는 데 사용되는 OVERLAPPED 구조체
	//)
	if (false == SocketUtils::ConnectEx(m_socket, reinterpret_cast<SOCKADDR*>(&m_sockAddr), sizeof(m_sockAddr), nullptr, 0, &_numOfBytes, &m_connectEvent))
	{
		__int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			m_connectEvent.m_owner = nullptr;
			return false;
		}
	}

	return true;
}

bool Session::RegisterDisconnect()
{
	DebugLog("[%s]", __FUNCTION__);
	m_disconnectEvent.Init();
	m_disconnectEvent.m_owner = shared_from_this();

	//https://learn.microsoft.com/ko-kr/windows/win32/api/mswsock/nc-mswsock-lpfn_disconnectex
	//BOOL DisconnectEx(
	//	_In_ SOCKET       hSocket,			: 연결된 소켓
	//	_In_ LPOVERLAPPED lpOverlapped,		: OVERLAPPED 구조에 대한 포인터
	//	_In_ DWORD        dwFlags,			: TF_REUSE_SOCKET 세팅 시, 다시 사용할 소켓 핸들을 준비 이렇게 세팅된 소캣은 다시, AcceptEx 또는 ConnectEx 에 전달 될 수 있음.
	//	_In_ DWORD        reserved			: 0임
	//);

	if (false == SocketUtils::DisconnectEx(m_socket, &m_disconnectEvent, TF_REUSE_SOCKET, 0))
	{
		__int32 _errorCode = ::WSAGetLastError();
		if (_errorCode != WSA_IO_PENDING)
		{
			m_disconnectEvent.m_owner = nullptr;
			return false;
		}
	}

	return true;
}

void Session::RegisterRecv()
{
	DebugLog("[%s]", __FUNCTION__);
	if (IsConnected() == false)
		return;

	m_recvEvent.Init();
	m_recvEvent.m_owner = shared_from_this();

	WSABUF _wsaBuf;
	_wsaBuf.buf = reinterpret_cast<char*>(m_recvBuffer.GetWritePos());
	_wsaBuf.len = m_recvBuffer.GetFreeSize();

	DWORD _numOfBytes = 0;
	DWORD _flags = 0;

	//https://learn.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-wsarecv
	//int WSAAPI WSARecv(
	//	[in]      SOCKET                             s,						연결된 소켓
	//	[in, out] LPWSABUF                           lpBuffers,				WSABUF 구조체 배열에 대한 포인터
	//	[in]      DWORD                              dwBufferCount,			lpBuffers 안의 WSABUF 구조체 수
	//	[out]     LPDWORD                            lpNumberOfBytesRecvd,	작업이 즉시 완료되는 경우 이 호출에서 받은 데이터의 수(바이트)
	//	[in, out] LPDWORD                            lpFlags,				함수 호출 동작 수정 시 이용. 보통 0
	//	[in]      LPWSAOVERLAPPED                    lpOverlapped,			WSAOVERLAPPED 구조체에 대한 포인터 (오버렙 사용 안하면, null)
	//	[in]      LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine	수신 작업이 완료되었을 때 호출되는 완료 루틴 (오버렙 사용 시)
	//);

	if (SOCKET_ERROR == ::WSARecv(m_socket, &_wsaBuf, 1, OUT & _numOfBytes, OUT & _flags, &m_recvEvent, nullptr))
	{
		__int32 errorCode = ::WSAGetLastError();
		if (errorCode != WSA_IO_PENDING)
		{
			HandleError(errorCode);
			m_recvEvent.m_owner = nullptr;
		}
	}
}

void Session::RegisterSend()
{
	DebugLog("[%s]", __FUNCTION__);
	if (IsConnected() == false)
		return;

	m_sendEvent.Init();
	m_sendEvent.m_owner = shared_from_this();

	{
		lock_guard<recursive_mutex> _lock(m_lock);

		__int32 m_writeSize = 0;
		while (m_sendQueue.empty() == false)
		{
			shared_ptr<SendBuffer> _sendBuffer = m_sendQueue.front();

			m_writeSize += _sendBuffer->GetWriteSize();
			
			if (m_writeSize >= 4000) //BYTE버퍼 4KB에 가깝게
				break;

			m_sendQueue.pop();
			m_sendEvent.m_sendBufferList.push_back(_sendBuffer);
		}
	}

	vector<WSABUF> _wsaBufs;
	_wsaBufs.reserve(m_sendEvent.m_sendBufferList.size());
	for (shared_ptr<SendBuffer> sendBuffer : m_sendEvent.m_sendBufferList)
	{
		WSABUF _wsaBuf;
		_wsaBuf.buf = reinterpret_cast<char*>(sendBuffer->GetBuffer());
		_wsaBuf.len = static_cast<LONG>(sendBuffer->GetWriteSize());

		_wsaBufs.push_back(_wsaBuf);
	}

	DWORD _numOfBytes = 0;

	//https://learn.microsoft.com/ko-kr/windows/win32/api/winsock2/nf-winsock2-wsasend
	//int WSAAPI WSASend(
	//	[in]  SOCKET                             s,						: 연결된 소켓
	//	[in]  LPWSABUF                           lpBuffers,				: WSABUF 구조체 배열에 대한 포인터
	//	[in]  DWORD                              dwBufferCount,			: lpBuffers 안의 WSABUF 구조체 수
	//	[out] LPDWORD                            lpNumberOfBytesSent,	: 작업이 즉시 완료되는 경우 이 호출에서 보낸 숫자(바이트)
	//	[in]  DWORD                              dwFlags,				: 연결된 소켓에 대해 지정된 옵션 외 추가옵션 세팅 가능 0으로 세팅.
	//	[in]  LPWSAOVERLAPPED                    lpOverlapped,			: WSAOVERLAPPED 구조체에 대한 포인터 (오버렙 사용 안하면, null)
	//	[in]  LPWSAOVERLAPPED_COMPLETION_ROUTINE lpCompletionRoutine	: 수신 작업이 완료되었을 때 호출되는 완료 루틴 (오버렙 사용 시)
	//);
	if (SOCKET_ERROR == ::WSASend(m_socket, _wsaBufs.data(), static_cast<DWORD>(_wsaBufs.size()), OUT & _numOfBytes, 0, &m_sendEvent, nullptr))
	{
		__int32 _errorCode = ::WSAGetLastError();
		if (_errorCode != WSA_IO_PENDING)
		{
			HandleError(_errorCode);
			m_sendEvent.m_owner = nullptr;
			m_sendEvent.m_sendBufferList.clear();
			m_sendRegistered.store(false);
		}
	}
}

void Session::ProcessConnect()
{
	DebugLog("[%s]", __FUNCTION__);
	m_connectEvent.m_owner = nullptr;
	m_connected.store(true);

	GetService()->AddSession(GetSessionRef());

	OnConnected();

	RegisterRecv();
}

void Session::ProcessDisconnect()
{
	m_disconnectEvent.m_owner = nullptr;
}

void Session::ProcessRecv(__int32 numOfBytes)
{
	DebugLog("[%s]", __FUNCTION__);
	m_recvEvent.m_owner = nullptr;

	if (numOfBytes == 0)
	{
		Disconnect(L"Recv 0");
		return;
	}

	if (m_recvBuffer.OnWrite(numOfBytes) == false)
	{
		Disconnect(L"OnWrite Overflow");
		return;
	}

	__int32 _dataSize = m_recvBuffer.GetDataSize();
	__int32 _processLen = OnRecv(m_recvBuffer.GetReadPos(), _dataSize);
	if (_processLen < 0 || _dataSize < _processLen || m_recvBuffer.OnRead(_processLen) == false)
	{
		Disconnect(L"OnRead Overflow");
		return;
	}

	m_recvBuffer.Clean();

	RegisterRecv();
}

void Session::ProcessSend(__int32 numOfBytes)
{
	DebugLog("[%s]", __FUNCTION__);
	m_sendEvent.m_owner = nullptr;
	m_sendEvent.m_sendBufferList.clear();

	if (numOfBytes == 0)
	{
		Disconnect(L"Send 0");
		return;
	}

	OnSend(numOfBytes);
	{
		lock_guard<recursive_mutex> _lock(m_lock);
		if (m_sendQueue.empty())
			m_sendRegistered.store(false);
		else
			RegisterSend();
	}
}

void Session::HandleError(__int32 errorCode)
{
	switch (errorCode)
	{
	case WSAECONNRESET:
	case WSAECONNABORTED:
		Disconnect(L"HandleError");
		break;
	default:
		DebugLog("[%s] Handle Error [%d]: ", __FUNCTION__, errorCode);
		break;
	}
}