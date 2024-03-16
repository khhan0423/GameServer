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
//���� ��, IOCPObject owner ����Ʈ�����Ϳ� CompletionPort�ڵ��� ����Ʈ�����͸� �Ѱ��ִ� ������� ���� �Ѵ�.
//��.���� ���۸� �����ϰ� �ִ�.
class Session : public IocpObject
{

private:	
	//GetHandle, Dispatch �� �ݵ�� ����.
	virtual HANDLE							GetHandle() override;
	virtual void							Dispatch(class IocpEvent* iocpEvent, __int32 numOfBytes = 0) override;

private:
	friend class Listener; //Listener ���� Session�� ���Ź��۸� �����Ͽ� AcceptEx�� ȣ���Ͽ��� ��.
	//friend class IocpCore;
	friend class Service;

	enum
	{
		BUFFER_SIZE = 0x10000, // 64KB
	};

public:
	Session();
	virtual ~Session();

public:
	void									Send(shared_ptr<SendBuffer> sendBuffer);
	bool									Connect();
	void									Disconnect(const WCHAR* cause);

	shared_ptr<Service>						GetService() { return _service.lock(); }
	void									SetService(shared_ptr<Service> service) { _service = service; }

public:
	void									SetNetAddress(NetAddress address) { _netAddress = address; }
	NetAddress								GetAddress() { return _netAddress; }
	SOCKET									GetSocket() { return _socket; }
	bool									IsConnected() { return _connected; }
	shared_ptr<Session>						GetSessionRef() { return static_pointer_cast<Session>(shared_from_this()); }

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
	weak_ptr<Service>						_service;
	SOCKET									_socket = INVALID_SOCKET;
	NetAddress								_netAddress = {};
	atomic<bool>							_connected = false;

private:
	recursive_mutex							_lock;

private:
	RecvBuffer								_recvBuffer;
	queue<shared_ptr<SendBuffer>>			_sendQueue;
	atomic<bool>							_sendRegistered = false;

private:
	ConnectEvent							_connectEvent;
	DisconnectEvent							_disconnectEvent;
	RecvEvent								_recvEvent;
	SendEvent								_sendEvent;
};