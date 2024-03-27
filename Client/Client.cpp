#include "pch.h"
#include "LogBase.h"
#include "ClientNetworkSystem.h"
#include "DummyClient.h"


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

	ClinetSystem()->Init();
	if (ClinetSystem()->Construct(APP_WITDH, APP_HEIGH, 4, 4))
		ClinetSystem()->Start(); //loop

	return 0;
}
