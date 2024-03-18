#include "pch.h"
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

	const __int32 acceptCount = m_service->GetMaxSessionCount();
	for (__int32 i = 0; i < acceptCount; i++)
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
