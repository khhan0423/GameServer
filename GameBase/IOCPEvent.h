#pragma once
#include <vector>

class IocpObject;
class Session;
class SendBuffer;

enum class EventType : unsigned __int16
{
	eCONNECT,
	eDISCONNECT,
	eACCEPT,
	eRECV,
	eSEND
};

//OVERLAPPED 를 상속받은 IocpEvent
//IocpEvent를 재사용 하기 위해 owner를 스마트 포인터로 선언했다.
class IocpEvent : public OVERLAPPED
{
public:
	IocpEvent(EventType type);

	void					Init();

public:
	EventType				m_eventType;
	shared_ptr<IocpObject>	m_owner;
};


class ConnectEvent : public IocpEvent
{
public:
	ConnectEvent() : IocpEvent(EventType::eCONNECT) { }
};

class DisconnectEvent : public IocpEvent
{
public:
	DisconnectEvent() : IocpEvent(EventType::eDISCONNECT) { }
};

class AcceptEvent : public IocpEvent
{
public:
	AcceptEvent() : IocpEvent(EventType::eACCEPT) { }

public:
	shared_ptr<Session>	session = nullptr;
};

class RecvEvent : public IocpEvent
{
public:
	RecvEvent() : IocpEvent(EventType::eRECV) { }
};

class SendEvent : public IocpEvent
{
public:
	SendEvent() : IocpEvent(EventType::eSEND) { }

	vector<shared_ptr<SendBuffer>> m_sendBufferList;
};

