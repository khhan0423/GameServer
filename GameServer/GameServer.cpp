#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "SocketUtils.h"
#include "GlobalGameBase.h"
#include "ThreadManager.h"
#include "ClientPacketHandler.h"
#include "LogBase.h"

enum
{
	WORKER_TICK = 64
};

void DoWorkerJob(shared_ptr<ServerService>& service)
{
	while (true)
	{
		TLS_EndTickCount = ::GetTickCount64() + WORKER_TICK;
		
		service->GetIocpCore()->Dispatch(10);

		GThreadManager->Run();
		//GetThreadManager()->Run();
	}
}

int main()
{
	ClientPacketHandler::Init();
	GetGlobalLog()->Init(GAMELOG_LEVEL_DEBUG, GAMELOG_OUTPUT_BOTH, "GameServer");

	shared_ptr<ServerService> _service = make_shared<ServerService>(
		NetAddress(L"127.0.0.1", 7777),
		move(make_shared<IocpCore>())/*rValue move 로 포장해서 넘김*/,
		move(make_shared<GameSession>)/*rValue move 로 포장해서 넘김*/,
		5);

	VERIFY(_service->Start());

	for (__int32 i = 0; i < 2; i++)
	{
		GThreadManager->Launch([&_service]()
		//GetThreadManager()->Launch([&_service]()
			{
				while (true)
				{
					DoWorkerJob(_service);
				}
			});
	}

	DoWorkerJob(_service);

	GThreadManager->Join();
	//GetThreadManager()->Join();

	return 0;
}