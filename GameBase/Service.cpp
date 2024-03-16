#include "pch.h"
#include "Service.h"

Service::Service(ServiceType type, NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount)
	: m_type(type), m_netAddress(address), m_iocpCore(core), m_sessionFactory(factory), m_maxSessionCount(maxSessionCount)
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
	shared_ptr<Session> _session = m_sessionFactory();
	_session->SetService(shared_from_this());

	if (m_iocpCore->Register(_session) == false)
		return nullptr;

	return _session;
}

void Service::AddSession(shared_ptr<Session> session)
{
	{
		lock_guard<recursive_mutex> _lock(m_lock);
		m_sessionCount++;
		m_sessions.insert(session);
	}
}

void Service::ReleaseSession(shared_ptr<Session> session)
{
	{
		lock_guard<recursive_mutex> _lock(m_lock);
		ASSERT(m_sessions.erase(session) != 0);
		m_sessionCount--;
	}
}

ClientService::ClientService(NetAddress targetAddress, shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount)
	: Service(ServiceType::Client, targetAddress, core, factory, maxSessionCount)
{
}

bool ClientService::Start()
{
	if (CanStart() == false)
		return false;

	const __int32 _sessionCount = GetMaxSessionCount();
	for (__int32 i = 0; i < _sessionCount; i++)
	{
		shared_ptr<Session> session = CreateSession();
		if (session->eCONNECT() == false)
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

	m_listener = make_shared<Listener>();
	if (m_listener == nullptr)
		return false;

	shared_ptr<ServerService> _service = static_pointer_cast<ServerService>(shared_from_this());
	if (m_listener->StartAccept(_service) == false)
		return false;

	return true;
}

void ServerService::CloseService()
{

	Service::CloseService();
}
