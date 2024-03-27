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

	DummyClient _dummy;
	_dummy.Init();

	if (_dummy.Construct(APP_WITDH, APP_HEIGH, 4, 4))
		_dummy.Start();	

	return 0;
}
