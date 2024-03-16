#include "pch.h"
#include "IOCPEvent.h"

IocpEvent::IocpEvent(EventType type) : m_eventType(type)
{
	Init();
}

void IocpEvent::Init()
{
	//상속받은 OVERLAPPED 구조체 초기화.
	OVERLAPPED::hEvent = 0;
	OVERLAPPED::Internal = 0;
	OVERLAPPED::InternalHigh = 0;
	OVERLAPPED::Offset = 0;
	OVERLAPPED::OffsetHigh = 0;
}
