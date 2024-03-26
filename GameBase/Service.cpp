#include "pch.h"
#include "LogBase.h"
#include "Service.h"

Service::Service(ServiceType type, NetAddress address, std::shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount)
	: m_type(type), m_netAddress(address), m_iocpCore(core), m_sessionFactory(factory), m_maxSessionCount(maxSessionCount)
{
	DebugLog("[%s]", __FUNCTION__);
}

Service::~Service()
{
	DebugLog("[%s]", __FUNCTION__);
}

void Service::CloseService()
{
	DebugLog("[%s]", __FUNCTION__);
}

std::shared_ptr<Session> Service::CreateSession()
{
	std::shared_ptr<Session> _session = m_sessionFactory();
	_session->SetService(shared_from_this());

	DebugLog("[%s]", __FUNCTION__);
	if (m_iocpCore->Register(_session) == false)
		return nullptr;

	return _session;
}

void Service::AddSession(std::shared_ptr<Session> session)
{
	DebugLog("[%s]", __FUNCTION__);
	{
		std::lock_guard<std::recursive_mutex> _lock(m_lock);
		m_sessionCount.fetch_add(1);
		m_sessions.insert(session);
	}
}

void Service::ReleaseSession(std::shared_ptr<Session> session)
{
	DebugLog("[%s]", __FUNCTION__);
	{
		std::lock_guard<std::recursive_mutex> _lock(m_lock);
		VERIFY(m_sessions.erase(session) != 0);
		m_sessionCount.fetch_sub(1);
	}
}

ClientService::ClientService(NetAddress targetAddress, std::shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount)
	: Service(ServiceType::Client, targetAddress, core, factory, maxSessionCount)
{
}

bool ClientService::Start()
{
	DebugLog("[%s]", __FUNCTION__);
	if (CanStart() == false)
		return false;

	const __int32 _sessionCount = GetMaxSessionCount();
	for (__int32 i = 0; i < _sessionCount; i++)
	{
		std::shared_ptr<Session> session = CreateSession();
		if (session->Connect() == false)
			return false;
	}

	return true;
}

ServerService::ServerService(NetAddress address, std::shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount)
	: Service(ServiceType::Server, address, core, factory, maxSessionCount)
{
	DebugLog("[%s]", __FUNCTION__);
}

bool ServerService::Start()
{
	DebugLog("[%s]", __FUNCTION__);
	if (CanStart() == false)
		return false;

	m_listener = std::make_shared<Listener>();
	if (m_listener == nullptr)
		return false;

	std::shared_ptr<ServerService> _service = std::static_pointer_cast<ServerService>(shared_from_this());
	if (m_listener->StartAccept(_service) == false)
		return false;

	return true;
}

void ServerService::CloseService()
{
	DebugLog("[%s]", __FUNCTION__);
	Service::CloseService();
}
