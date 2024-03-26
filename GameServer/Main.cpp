#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "SocketUtils.h"
#include "GameServerSystem.h"
#include "SQLiteManager.h"

void  MainThreadFunc()
{
	while (true)
	{
		GetDBManager()->Update();
		std::this_thread::sleep_for(std::chrono::microseconds(1));
	}
}


int main()
{
	GameServer()->Init();

	MainThreadFunc();

	return 0;
}