#include "pch.h"
#include "Session.h"
#include "SocketUtils.h"
#include "RecvBuffer.h"
#include "SendBuffer.h"

Session::Session() : m_recvBuffer(BUFFER_SIZE)
{
	m_socket = SocketUtils::CreateSocket();
}

Session::~Session()
{
	SocketUtils::Close(m_socket);
}

void Session::Send(shared_ptr<SendBuffer> sendBuffer)
{
	{
		lock_guard<recursive_mutex> _lock(m_lock);

		m_sendQueue.push(sendBuffer);

		if (m_sendRegistered.exchange(true) == false)
			RegisterSend();
	}
}

bool Session::Connect()
{
	return RegisterConnect();
}

void Session::Disconnect(const WCHAR* cause)
{
	if (m_connected.exchange(false) == false)
		return;	

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
	if (IsConnected())
		return false;

	if (GetService()->GetServiceType() != ServiceType::Client)
		return false;

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
	m_disconnectEvent.Init();
	m_disconnectEvent.m_owner = shared_from_this();

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
	if (IsConnected() == false)
		return;

	m_recvEvent.Init();
	m_recvEvent.m_owner = shared_from_this();

	WSABUF _wsaBuf;
	_wsaBuf.buf = reinterpret_cast<char*>(m_recvBuffer.GetWritePos());
	_wsaBuf.len = m_recvBuffer.GetFreeSize();

	DWORD _numOfBytes = 0;
	DWORD _flags = 0;
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
		// TODO : Log
		cout << "Handle Error : " << errorCode << endl;
		break;
	}
}