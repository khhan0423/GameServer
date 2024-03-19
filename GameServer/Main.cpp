#include "pch.h"
#include "Service.h"
#include "Session.h"
#include "GameSession.h"
#include "SocketUtils.h"
#include "GameServerSystem.h"

int main()
{
	GameServer()->Init();

	while (true)
	{
		//콘솔환경에서는 무한루프 안돌면 main이 return 되면서
		//전역 클레스 객체가 소멸자를 호출하는군...
		//윈Main 환경에서만 서버짜다가 처음 알았음.. 와..
		this_thread::yield();
	}
	return 0;
}