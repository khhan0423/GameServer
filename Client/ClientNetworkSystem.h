#pragma once
#include "Service.h"
#include "SingletonBase.h"

#define NetworkSystem() ClientNetworkSystem::GetInstance()

class ClientNetworkSystem : public TSingletonBase<ClientNetworkSystem>
{
public:
	ClientNetworkSystem() {};
	~ClientNetworkSystem() { Release(); }

	void									Init();
	void									Shutdown();
	bool									StartConnect();

	void									Send(std::shared_ptr<SendBuffer> sendBuffer);

private:
	enum
	{
		WORKER_TICK = 64
	};
private:
	bool									Initialize();
	bool									OnInitialize();
	void									Release();

	void									Intiate();
	void									OnIntiate();
	void									ThreadRun();

	std::atomic<bool>						m_isReady = false;
	std::atomic<bool>						m_isQuit = false;

private:
	std::shared_ptr<ClientService>			m_networkService;
};

