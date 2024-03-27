#pragma once
#include "OLCEngine/extensions/olcPGEX_QuickGUI.h"
#include "SeneStateChanger.h"
class DummyClient : public olc::PixelGameEngine
{
public:
	SeneStateChanger* m_SceneChanger = nullptr;
public:
	DummyClient()
	{
		sAppName = "GAME SERVER DEMO Dummy Client";
	}

	void Init();

public:
	bool OnUserCreate() override;
	bool OnUserUpdate(float fElapsedTime) override;
	olc::QuickGUI::Manager guiManager;
};

