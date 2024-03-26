#include "pch.h"

#include "LogBase.h"
#include "GlobalGameBase.h"
#include "ThreadManager.h"
#include "ServerPacketHandler.h"
#include "ClientGameSession.h"
#include "ClientNetworkSystem.h"

void ClientNetworkSystem::Init()
{
	Initialize();
}

bool ClientNetworkSystem::Initialize()
{
	//초기값 세팅 및 Config 들 로딩
	ServerPacketHandler::Init();
	GetGlobalLog()->Init(GAMELOG_LEVEL_DEBUG, GAMELOG_OUTPUT_BOTH, "Client");
	if (false == OnInitialize())
	{
		ErrorLog("[%s] fail - OnInitialize()", __FUNCTION__);
		exit(1);
	}

	return true;
}

bool ClientNetworkSystem::OnInitialize()
{
	//서버 서비스가 시작되기 전에 미리 로딩되어야 할 종류의 메니저들을 시작한다.

	Intiate();

	return true;
}

void ClientNetworkSystem::Release()
{
	GThreadManager->Join();
}

void ClientNetworkSystem::Intiate()
{
	m_networkService = std::make_shared<ClientService>(
		NetAddress(L"127.0.0.1", 7777),
		move(std::make_shared<IocpCore>())/*rValue move 로 포장해서 넘김*/,
		move(std::make_shared<ClientGameSession>)/*rValue move 로 포장해서 넘김*/,
		1);

	VERIFY(m_networkService->Start());

	OnIntiate();
}

void ClientNetworkSystem::OnIntiate()
{
	m_isReady.exchange(true);

	for (__int32 i = 0; i < 1; i++)
	{
		GThreadManager->Launch([this]()
			{
				while (true)
				{
					ThreadRun();
				}
			});
	}	
}

void ClientNetworkSystem::ThreadRun()
{
	while (true)
	{
		if (m_isReady == false)
			std::this_thread::yield();

		TLS_EndTickCount = ::GetTickCount64() + WORKER_TICK;

		m_networkService->GetIocpCore()->Dispatch(10);

		GThreadManager->Run();
	}
}