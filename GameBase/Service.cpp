#include "pch.h"
#include "Service.h"

Service::Service(ServiceType type, NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount)
	: _type(type), _netAddress(address), _iocpCore(core), _sessionFactory(factory), _maxSessionCount(maxSessionCount)
{

}

Service::~Service()
{
}

void Service::CloseService()
{

}

shared_ptr<Session> Service::CreateSession()
{
	shared_ptr<Session> session = _sessionFactory();
	session->SetService(shared_from_this());

	if (_iocpCore->Register(session) == false)
		return nullptr;

	return session;
}

void Service::AddSession(shared_ptr<Session> session)
{
	lock_guard<recursive_mutex> lock(_lock);
	_sessionCount++;
	_sessions.insert(session);
}

void Service::ReleaseSession(shared_ptr<Session> session)
{
	lock_guard<recursive_mutex> lock(_lock);
	ASSERT(_sessions.erase(session) != 0);
	_sessionCount--;
}

ClientService::ClientService(NetAddress targetAddress, shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount)
	: Service(ServiceType::Client, targetAddress, core, factory, maxSessionCount)
{
}

bool ClientService::Start()
{
	if (CanStart() == false)
		return false;

	const __int32 sessionCount = GetMaxSessionCount();
	for (__int32 i = 0; i < sessionCount; i++)
	{
		shared_ptr<Session> session = CreateSession();
		if (session->Connect() == false)
			return false;
	}

	return true;
}

ServerService::ServerService(NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount)
	: Service(ServiceType::Server, address, core, factory, maxSessionCount)
{
}

bool ServerService::Start()
{
	if (CanStart() == false)
		return false;

	_listener = make_shared<Listener>();
	if (_listener == nullptr)
		return false;

	shared_ptr<ServerService> service = static_pointer_cast<ServerService>(shared_from_this());
	if (_listener->StartAccept(service) == false)
		return false;

	return true;
}

void ServerService::CloseService()
{

	Service::CloseService();
}
