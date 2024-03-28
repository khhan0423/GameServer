#pragma once
#include <vector>

#include "IOCPCore.h"

class AcceptEvent;
class ServerService;

class Listener : public IocpObject
{
public:
	Listener(const unsigned __int32 listernCnt) : m_ListenCount(listernCnt) {}
	Listener() = default;
	~Listener();

public:
	virtual HANDLE					GetHandle() override;
	virtual void					Dispatch(class IocpEvent* iocpEventPtr, __int32 numOfBytes = 0) override;

public:
	bool							StartAccept(std::shared_ptr<ServerService> serviceShared);
	void							CloseSocket();

private:
	void							RegisterAccept(AcceptEvent* acceptEventPtr);
	void							ProcessAccept(AcceptEvent* acceptEventPtr);

protected:
	unsigned __int32				m_ListenCount = 5;
	SOCKET							m_socket = INVALID_SOCKET;
	std::vector<AcceptEvent*>		m_acceptEvents;
	std::shared_ptr<ServerService>	m_service;
};