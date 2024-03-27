#include "pch.h"
#include "GlobalGameBase.h"
#include "LogBase.h"
#include "ClientNetworkSystem.h"
#include "DummyClient.h"
#include <future>
#include <thread>

int main()
{
#ifdef _DEBUG
#else
	HWND consoleWindow = GetConsoleWindow();
	ShowWindow(consoleWindow, SW_HIDE);
#endif


	std::this_thread::sleep_for(std::chrono::seconds(1));

	NetworkSystem()->Init();

	ClinetSystem()->Init();
	if (ClinetSystem()->Construct(APP_WITDH, APP_HEIGH, 4, 4))
		ClinetSystem()->Start(); //loop in PixelGameEngine thread.		

	return 0;
}
