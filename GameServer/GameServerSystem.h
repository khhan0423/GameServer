#pragma once
#include "Service.h"
#include "SingletonBase.h"

#define GameServer() GameServerSystem::GetInstance()

class GameServerSystem : public SingletonBase<GameServerSystem>
{
public:
	GameServerSystem();
	~GameServerSystem() { Release(); }

private:
	bool								Initialize();
	void								Release();
										
	void								Intiate();
	void								Run();
	
	void								CheckAnotherServers();

	atomic<bool>						m_isReady = false;

private:
	shared_ptr<ServerService>			m_service;
};

