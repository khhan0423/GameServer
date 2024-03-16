#pragma once
#include <vector>

#include "IOCPCore.h"

class AcceptEvent;
class ServerService;

class Listener : public IocpObject
{
public:
	Listener() = default;
	~Listener();

public:
	virtual HANDLE GetHandle() override;
	virtual void Dispatch(class IocpEvent* iocpEvent, __int32 numOfBytes = 0) override;

public:
	bool StartAccept(shared_ptr<ServerService> service);
	void CloseSocket();

private:
	void RegisterAccept(AcceptEvent* acceptEvent);
	void ProcessAccept(AcceptEvent* acceptEvent);

protected:
	SOCKET						m_socket = INVALID_SOCKET;
	vector<AcceptEvent*>		m_acceptEvents;
	shared_ptr<ServerService>	m_service;
};