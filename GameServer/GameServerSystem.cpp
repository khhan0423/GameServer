#include "pch.h"
#include "GameServerSystem.h"
#include "GameSession.h"
#include "GlobalGameBase.h"
#include "ThreadManager.h"
#include "ClientPacketHandler.h"
#include "LogBase.h"
#include "SQLiteManager.h"
#include "ItemTable.h"

void GameServerSystem::Init()
{
	Initialize();
}

bool GameServerSystem::Initialize()
{
	//�ʱⰪ ���� �� Config �� �ε�
	ClientPacketHandler::Init();
	GetGlobalLog()->Init(GAMELOG_LEVEL_DEBUG, GAMELOG_OUTPUT_BOTH, "GameServer");
	if (false == OnInitialize())
	{
		ErrorLog("[%s] fail - OnInitialize()", __FUNCTION__);
		exit(1);
	}

	return true;
}

bool GameServerSystem::OnInitialize()
{
	//���� ���񽺰� ���۵Ǳ� ���� �̸� �ε��Ǿ�� �� ������ �޴������� �����Ѵ�.

	VERIFY_FAILED(GetItemTable()->Load())
	{
		ErrorLog("[%s] ItemTable  - Load fail()", __FUNCTION__);
	}

	
	VERIFY_FAILED(GetDBManager()->Start()) //DB �Ŵ��� ����
	{
		ErrorLog("[%s] fail - GetDBManager()->Start()", __FUNCTION__);
		return false;
	}


	Intiate();

	return true;
}

void GameServerSystem::Release()
{
	GThreadManager->Join();
}
 
void GameServerSystem::Intiate() 
{
	m_serviceForClient = std::make_shared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		move(std::make_shared<IocpCore>())/*rValue move �� �����ؼ� �ѱ�*/,
		move(std::make_shared<GameSession>)/*rValue move �� �����ؼ� �ѱ�*/,
		1);

	VERIFY(m_serviceForClient->Start());

	OnIntiate();
}

void GameServerSystem::OnIntiate()
{
	m_isReady.exchange(true);

	for (__int32 i = 0; i < 2; i++)
	{
		GThreadManager->Launch([this]()
			{
				while (true)
				{
					ThreadRun();
				}
			});
	}

	GetDBManager()->SetReady();
}

void GameServerSystem::ThreadRun()
{

	while (true)
	{
		if (m_isReady == false)
			std::this_thread::yield();

		TLS_EndTickCount = ::GetTickCount64() + WORKER_TICK;

		m_serviceForClient->GetIocpCore()->Dispatch(10);

		GThreadManager->Run();
	}
}

void GameServerSystem::CheckAnotherServers()
{
	//to - do
	//for hear bear with another servers.
}
