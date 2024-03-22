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
		this_thread::sleep_for(chrono::microseconds(1));
	}
}


int main()
{
	GameServer()->Init();

	MainThreadFunc();

	return 0;
}