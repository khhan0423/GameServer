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

//OVERLAPPED 를 상속받은 IocpEvent
//IocpEvent를 재사용 하기 위해 owner를 스마트 포인터로 선언했다.
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

