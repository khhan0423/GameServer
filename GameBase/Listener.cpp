#include "pch.h"
#include "LogBase.h"
#include "Listener.h"
#include "SocketUtils.h"
#include "Session.h"
#include "Service.h"

Listener::~Listener()
{
	DebugLog("[%s]", __FUNCTION__);
	SocketUtils::Close(m_socket);

	for (AcceptEvent* _acceptEvent : m_acceptEvents)
	{
		if(_acceptEvent != nullptr)
			SAFE_DELETE(_acceptEvent);
	}		
}

bool Listener::StartAccept(shared_ptr<ServerService> service)
{
	DebugLog("[%s]", __FUNCTION__);
	m_service = service;
	if (m_service == nullptr)
		return false;

	m_socket = SocketUtils::CreateSocket();
	if (m_socket == INVALID_SOCKET)
		return false;

	if (m_service->GetIocpCore()->Register(shared_from_this()) == false)
		return false;

	//SO_REUSEADDR 세팅을 해야, 
	if (SocketUtils::SetReuseAddress(m_socket, true) == false)
		return false;

	if (SocketUtils::SetTcpNoDelay(m_socket, true) == false)
		return false;

	if (SocketUtils::SetLinger(m_socket, 0, 0) == false)
		return false;

	if (SocketUtils::Bind(m_socket, m_service->GetNetAddress()) == false)
		return false;

	if (SocketUtils::Listen(m_socket) == false)
		return false;

	for (unsigned __int32 i = 0; i < m_ListenCount; i++)
	{
		AcceptEvent* acceptEvent = new AcceptEvent();
		acceptEvent->m_owner = shared_from_this();
		m_acceptEvents.push_back(acceptEvent);
		RegisterAccept(acceptEvent);
	}

	return true;
}

void Listener::CloseSocket()
{
	DebugLog("[%s]", __FUNCTION__);
	SocketUtils::Close(m_socket);
}

HANDLE Listener::GetHandle()
{
	return reinterpret_cast<HANDLE>(m_socket);
}

void Listener::Dispatch(IocpEvent* iocpEvent, __int32 numOfBytes)
{
	DebugLog("[%s]", __FUNCTION__);
	VERIFY(iocpEvent->m_eventType == EventType::eACCEPT);
	AcceptEvent* _acceptEventPtr = static_cast<AcceptEvent*>(iocpEvent);
	ProcessAccept(_acceptEventPtr);
}

void Listener::RegisterAccept(AcceptEvent* acceptEventPtr)
{
	DebugLog("[%s]", __FUNCTION__);
	shared_ptr<Session> _session = m_service->CreateSession();

	acceptEventPtr->Init();
	acceptEventPtr->session = _session;

	DWORD bytesReceived = 0;

	//https://learn.microsoft.com/ko-kr/windows/win32/api/mswsock/nf-mswsock-acceptex
	//BOOL AcceptEx(
	//	[in]  SOCKET       sListenSocket,				listen 함수를 이용하여, 수신대기 상태에 있는 소캣
	//	[in]  SOCKET       sAcceptSocket,				연결을 수락할 소켓	이 소켓은 바인딩되거나 연결되지 않아야 한다.
	//	[in]  PVOID        lpOutputBuffer,				새 연결에서 전송된 데이터의 첫 번째 블록, 서버의 로컬 주소 및 클라이언트의 원격 주소를 수신하는 버퍼에 대한 포인터입니다
	//	[in]  DWORD        dwReceiveDataLength,			lpOutputBuffer 바이트 수, 0으로 세팅하면, Accept가 완료 되어도 Revc 가 발생하지 않는다.
	//	[in]  DWORD        dwLocalAddressLength,		로컬 주소 정보를 위해 예약된 바이트 수 (최대 주소 길이보다 16바이트 이상이어야 합니다.)
	//	[in]  DWORD        dwRemoteAddressLength,		원격 주소 정보를 위해 예약된 바이트 수 (최대 주소 길이보다 16바이트 이상이어야 합니다.)
	//	[out] LPDWORD      lpdwBytesReceived,			받은 바이트 수를 수신하는 DWORD 에 대한 포인터 작업이 동기적으로 완료되는 경우에만 값이 발생
	//	[in]  LPOVERLAPPED lpOverlapped					요청을 처리하는 데 사용되는 OVERLAPPED 구조체 (Null 일 수 없다).
	//);
	if (false == SocketUtils::AcceptEx(m_socket, _session->GetSocket(), _session->m_recvBuffer.GetWritePos(), 0, sizeof(SOCKADDR_IN) + 16, sizeof(SOCKADDR_IN) + 16, OUT & bytesReceived, static_cast<LPOVERLAPPED>(acceptEventPtr)))
	{
		const __int32 _errorCode = ::WSAGetLastError();
		if (_errorCode != WSA_IO_PENDING)
		{
			RegisterAccept(acceptEventPtr);
		}
	}
}

void Listener::ProcessAccept(AcceptEvent* acceptEventPtr)
{
	DebugLog("[%s]", __FUNCTION__);
	shared_ptr<Session> _session = acceptEventPtr->session;

	if (false == SocketUtils::SetUpdateAcceptSocket(_session->GetSocket(), m_socket))
	{
		RegisterAccept(acceptEventPtr);
		return;
	}

	SOCKADDR_IN _sockAddress;
	__int32 sizeOfSockAddr = sizeof(_sockAddress);
	if (SOCKET_ERROR == ::getpeername(_session->GetSocket(), OUT reinterpret_cast<SOCKADDR*>(&_sockAddress), &sizeOfSockAddr))
	{
		RegisterAccept(acceptEventPtr);
		return;
	}

	_session->SetNetAddress(NetAddress(_sockAddress));
	_session->ProcessConnect();
	RegisterAccept(acceptEventPtr);
}
