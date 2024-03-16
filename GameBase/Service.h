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

using SessionFactory = function<shared_ptr<Session>(void)>;

class Service : public enable_shared_from_this<Service>
{
public:
	Service(ServiceType type, NetAddress address, shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount = 1);
	virtual ~Service();

	virtual bool						Start() abstract;
	bool								CanStart() { return _sessionFactory != nullptr; }

	virtual void						CloseService();
	void								SetSessionFactory(SessionFactory func) { _sessionFactory = func; }

	shared_ptr<Session>					CreateSession();
	void								AddSession(shared_ptr<Session> session);
	void								ReleaseSession(shared_ptr<Session> session);
	__int32								GetCurrentSessionCount() { return _sessionCount; }
	__int32								GetMaxSessionCount() { return _maxSessionCount; }

public:
	ServiceType							GetServiceType() { return _type; }
	NetAddress							GetNetAddress() { return _netAddress; }
	shared_ptr<IocpCore>&				GetIocpCore() { return _iocpCore; }

protected:
	recursive_mutex						_lock;

protected:
	ServiceType							_type;
	NetAddress							_netAddress = {};
	shared_ptr<IocpCore>				_iocpCore;

	set<shared_ptr<Session>>			_sessions;
	__int32								_sessionCount = 0;
	__int32								_maxSessionCount = 0;
	SessionFactory						_sessionFactory;
};

class ClientService : public Service
{
public:
	ClientService(NetAddress targetAddress, shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount = 1);
	virtual ~ClientService() {}

	virtual bool	Start() override;
};

class ServerService : public Service
{
public:
	ServerService(NetAddress targetAddress, shared_ptr<IocpCore> core, SessionFactory factory, __int32 maxSessionCount = 1);
	virtual ~ServerService() {}

	virtual bool				Start() override;
	virtual void				CloseService() override;

private:
	shared_ptr<Listener>		_listener = nullptr;
};