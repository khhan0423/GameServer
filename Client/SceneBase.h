#pragma once
#include "OLCEngine/extensions/olcPGEX_QuickGUI.h"

class SceneBase
{
public:
	SceneBase(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uimanager) : m_engine(engine), m_uiManager(uimanager) {}
public:
	virtual void begin()
	{
		//사용할 UI들을 보이게 처리해야 한다.
		for (__int32 cnt = 0; cnt < static_cast<__int32>(m_sceneControls.size()); cnt++)
		{
			if (m_sceneControls[cnt] == nullptr)
				continue;
			m_sceneControls[cnt]->Enable(true);
			m_sceneControls[cnt]->bVisible = true;
		}

		OnBegin();
	}
	virtual void OnBegin() abstract;
	virtual void run() abstract;
	virtual void complete()
	{
		//사용한 UI들을 안보이게 처리해야 한다.
		for (__int32 cnt = 0; cnt < static_cast<__int32>(m_sceneControls.size()); cnt++)
		{
			if (m_sceneControls[cnt] == nullptr)
				continue;
			m_sceneControls[cnt]->Enable(false);
			m_sceneControls[cnt]->bVisible = false;
		}
	}
	virtual ~SceneBase() {}


	olc::PixelGameEngine&						m_engine; //키보드 마우스 이벤트 가져오기 위해 필요
	olc::QuickGUI::Manager&						m_uiManager;
	std::vector<olc::QuickGUI::BaseControl*>	m_sceneControls; //이 콘트롤들의 포인터들은 엔진이 알아서 지운다.
};

