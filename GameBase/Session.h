#pragma once

#include <mutex>
#include <queue>

#include "IOCPCore.h"
#include "IOCPEvent.h"
#include "NetAddress.h"
#include "SendBuffer.h"
#include "RecvBuffer.h"
#include "Service.h"

//IocpObject�� ��ӹ޾�. CompletionPort �� ��������.
//IOCPEvent ���� ���� �����ϰ� �ִ�.
//IOCPEvent �� IOCPObject�� ��ӹ޾Ұ�,
//IOCPObject�� �����޴� CompletionPort�� �ڵ��� ����Ʈ�����͸� �����ϰ� ��������,
//���� ��, IOCPObject m_owner ����Ʈ�����Ϳ� CompletionPort�ڵ��� ����Ʈ�����͸� �Ѱ��ִ� ������� ���� �Ѵ�.
//��.���� ���۸� �����ϰ� �ִ�.
class Session : public IocpObject
{

private:	
	//GetHandle, Dispatch �� �ݵ�� ����.
	virtual HANDLE							GetHandle() override;
	virtual void							Dispatch(class IocpEvent* iocpEvent, __int32 numOfBytes = 0) override;

private:
	friend class Listener; //Listener ���� Session�� ���Ź��۸� �����Ͽ� AcceptEx�� ȣ���Ͽ��� ��.
	friend class Service;

	enum
	{
		BUFFER_SIZE = 0x10000, // 64KB
	};

public:
	Session();
	virtual ~Session();

public:
	void									Send(std::shared_ptr<SendBuffer> sendBufferShared);
	bool									Connect();
	void									Disconnect(const wchar_t* cause);

	std::shared_ptr<Service>				GetService() { return m_service.lock(); }
	void									SetService(std::shared_ptr<Service> serviceShared) { m_service = serviceShared; }

public:
	void									SetNetAddress(NetAddress address) { m_netAddress = address; }
	NetAddress								GetAddress() { return m_netAddress; }
	SOCKET									GetSocket() { return m_socket; }
	bool									IsConnected() { return m_connected; }
	std::shared_ptr<Session>				GetSessionRef() { return std::static_pointer_cast<Session>(shared_from_this()); }

public:
	void									SetSessionGUID(const unsigned __int64 key) { m_GUID = key; }
	unsigned __int64						GetSessionGUID() { return m_GUID; }

private:
	bool									RegisterConnect();
	bool									RegisterDisconnect();
	void									RegisterRecv();
	void									RegisterSend();

	void									ProcessConnect();
	void									ProcessDisconnect();
	void									ProcessRecv(__int32 numOfBytes);
	void									ProcessSend(__int32 numOfBytes);

	void									HandleError(__int32 errorCode);

protected:
	virtual void							OnConnected() { }
	virtual __int32							OnRecv(BYTE* buffer, __int32 len) { return len; }
	virtual void							OnSend(__int32 len) { }
	virtual void							OnDisconnected() { }

private:
	std::weak_ptr<Service>					m_service;
	SOCKET									m_socket = INVALID_SOCKET;
	NetAddress								m_netAddress = {};
	std::atomic<bool>						m_connected = false;

private:
	std::recursive_mutex					m_lock;

private:
	RecvBuffer								m_recvBuffer;
	std::queue<std::shared_ptr<SendBuffer>>	m_sendQueue;
	std::atomic<bool>						m_sendRegistered = false;

private:
	ConnectEvent							m_connectEvent;
	DisconnectEvent							m_disconnectEvent;
	RecvEvent								m_recvEvent;
	SendEvent								m_sendEvent;
private:
	unsigned __int64						m_GUID = 0;
};