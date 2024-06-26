#pragma once
#include "Service.h"
#include "SingletonBase.h"

#define GameServer() GameServerSystem::GetInstance()

class GameServerSystem : public TSingletonBase<GameServerSystem>
{
public:
	GameServerSystem() {};
	~GameServerSystem() { Release(); }

	void								Init();
	void								Shutdown();

private:
	enum
	{
		WORKER_TICK = 64
	};
private:
	bool								Initialize();
	bool								OnInitialize();
	void								Release();
										
	void								Intiate();
	void								OnIntiate();
	void								ThreadRun();
	
	void								CheckAnotherServers();

	std::atomic<bool>					m_isReady = false;

private:
	std::shared_ptr<ServerService>		m_serviceForClient;
};

