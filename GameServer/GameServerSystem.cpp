#include "pch.h"
#include "GameServerSystem.h"
#include "GameSession.h"
#include "GlobalGameBase.h"
#include "ThreadManager.h"
#include "ClientPacketHandler.h"
#include "LogBase.h"

GameServerSystem::GameServerSystem()
{
	Initialize();
}

bool GameServerSystem::Initialize()
{
	ClientPacketHandler::Init();
	GetGlobalLog()->Init(GAMELOG_LEVEL_DEBUG, GAMELOG_OUTPUT_BOTH, "GameServer");

	OnInitialize();

	return true;
}

bool GameServerSystem::OnInitialize()
{

	Intiate();

	return true;
}

void GameServerSystem::Release()
{
	GThreadManager->Join();
}
 
void GameServerSystem::Intiate() 
{
	m_service = make_shared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		move(make_shared<IocpCore>())/*rValue move 로 포장해서 넘김*/,
		move(make_shared<GameSession>)/*rValue move 로 포장해서 넘김*/,
		5);

	VERIFY(m_service->Start());

	OnIntiate();
}

void GameServerSystem::OnIntiate()
{
	shared_ptr<ServerService> _service = m_service;
	for (__int32 i = 0; i < 2; i++)
	{
		GThreadManager->Launch([this]()
			{
				while (true)
				{
					Run();
				}
			});
	}

	m_isReady.exchange(true);
}

void GameServerSystem::Run()
{
	while (true)
	{
		if (m_isReady == false)
			this_thread::yield();

		TLS_EndTickCount = ::GetTickCount64() + WORKER_TICK;

		m_service->GetIocpCore()->Dispatch(10);

		GThreadManager->Run();
	}
}

void GameServerSystem::CheckAnotherServers()
{
	//to - do
	//for hear bear with another servers.
}
