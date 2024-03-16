#pragma once
#include <vector>

class IocpObject;
class Session;
class SendBuffer;

enum class EventType : unsigned __int16
{
	Connect,
	Disconnect,
	Accept,
	Recv,
	Send
};

//OVERLAPPED �� ��ӹ��� IocpEvent
//IocpEvent�� ���� �ϱ� ���� owner�� ����Ʈ �����ͷ� �����ߴ�.
class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);

	void					Init();

public:
	EventType				eventType;
	shared_ptr<IocpObject>	owner;
};


class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent() : IocpEvent(EventType::Connect) { }
};

class DisconnectEvent : public IocpEvent
{
public:
	DisconnectEvent() : IocpEvent(EventType::Disconnect) { }
};

class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() : IocpEvent(EventType::Accept) { }

public:
	shared_ptr<Session>	session = nullptr;
};

class RecvEvent : public IocpEvent
{
public:
	RecvEvent() : IocpEvent(EventType::Recv) { }
};

class SendEvent : public IocpEvent
{
public:
	SendEvent() : IocpEvent(EventType::Send) { }

	vector<shared_ptr<SendBuffer>> sendBuffers;
};

