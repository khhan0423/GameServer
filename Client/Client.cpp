#include "pch.h"
#include "LogBase.h"
#include "ClientNetworkSystem.h"


void  MainThreadFunc()
{
	while (true)
	{
		std::this_thread::yield();
	}
}

int main()
{
	std::this_thread::sleep_for(std::chrono::seconds(1));

	NetworkSystem()->Init();

	MainThreadFunc();

	return 0;
}
