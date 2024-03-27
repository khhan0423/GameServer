#pragma once
#include "SingletonBase.h"
#include "OLCEngine/extensions/olcPGEX_QuickGUI.h"
#include "SeneStateChanger.h"

#define ClinetSystem() DummyClient::GetInstance()

class DummyClient : public olc::PixelGameEngine, public TSingletonBase<DummyClient>
{
public:
	SeneStateChanger* m_SceneChanger = nullptr;
public:
	DummyClient()
	{
		sAppName = "GAME SERVER DEMO Dummy Client";
	}

	void Init();

	bool OnUserDestroy() override
	{
		ExitProcess(0);
	}

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	olc::QuickGUI::Manager guiManager;
};

