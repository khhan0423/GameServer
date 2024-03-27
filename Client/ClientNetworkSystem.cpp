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

void ClientNetworkSystem::Shutdown()
{
	m_isQuit.exchange(true);
	Release();
	::ExitProcess(0);
}


bool ClientNetworkSystem::StartConnect()
{
	VERIFY(m_networkService->Start());

	return true;
}

void ClientNetworkSystem::Send(std::shared_ptr<SendBuffer> sendBuffer)
{
	m_networkService->m_serverSession->Send(sendBuffer);
}

bool ClientNetworkSystem::Initialize()
{
	//�ʱⰪ ���� �� Config �� �ε�
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
	//���� ���񽺰� ���۵Ǳ� ���� �̸� �ε��Ǿ�� �� ������ �޴������� �����Ѵ�.

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
		move(std::make_shared<IocpCore>())/*rValue move �� �����ؼ� �ѱ�*/,
		move(std::make_shared<ClientGameSession>)/*rValue move �� �����ؼ� �ѱ�*/,
		1);

	//Ŭ���̾�Ʈ UI �� �������� �۵���Ű�� �׽�Ʈ
	//VERIFY(m_networkService->Start());

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
		if (m_isQuit == true)
			break;

		if (m_isReady == false)
			std::this_thread::yield();

		TLS_EndTickCount = ::GetTickCount64() + WORKER_TICK;

		m_networkService->GetIocpCore()->Dispatch(10);

		GThreadManager->Run();

		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}