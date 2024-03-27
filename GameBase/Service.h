#pragma once
#include <functional>
#include <mutex>
#include <set>

#include "IOCPCore.h"
#include "Session.h"
#include "Listener.h"

class NetAddress;

enum class ServiceType : unsigned __int8
{
	Server,
	Client
};

using SessionFactory = std::function<std::shared_ptr<Session>(void)>;

class Service : public std::enable_shared_from_this<Service>
{
public:
	Service(ServiceType type, NetAddress address, std::shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount = 1);
	virtual ~Service();

	virtual bool								Start() abstract;
	bool										CanStart() { return m_sessionFactory != nullptr; }

	virtual void								CloseService();
	void										SetSessionFactory(SessionFactory func) { m_sessionFactory = func; }

	std::shared_ptr<Session>					CreateSession();
	void										AddSession(std::shared_ptr<Session> session);
	void										ReleaseSession(std::shared_ptr<Session> session);
	__int32										GetCurrentSessionCount() { return m_sessionCount; }
	__int32										GetMaxSessionCount() { return m_maxSessionCount; }

public:
	ServiceType									GetServiceType() { return m_type; }
	NetAddress									GetNetAddress() { return m_netAddress; }
	std::shared_ptr<IocpCore>&					GetIocpCore() { return m_iocpCore; }

protected:
	std::recursive_mutex						m_lock;

protected:
	ServiceType									m_type;
	NetAddress									m_netAddress = {};
	std::shared_ptr<IocpCore>					m_iocpCore;

	std::set<std::shared_ptr<Session>>			m_sessions;
	std::atomic<__int32>						m_sessionCount = 0;
	__int32										m_maxSessionCount = 0;
	SessionFactory								m_sessionFactory;
};

class ClientService : public Service
{
public:
	ClientService(NetAddress targetAddress, std::shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount = 1);
	virtual ~ClientService() {}

	virtual bool					Start() override;
public:
	std::shared_ptr<Session>		m_serverSession = nullptr;
};

class ServerService : public Service
{
public:
	ServerService(NetAddress targetAddress, std::shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount = 1);
	virtual ~ServerService() {}

	virtual bool				Start() override;
	virtual void				CloseService() override;

private:
	std::shared_ptr<Listener>		m_listener = nullptr;	
};