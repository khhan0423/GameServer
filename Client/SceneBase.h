#pragma once
#include "OLCEngine/extensions/olcPGEX_QuickGUI.h"
class SceneBase
{
public:
	SceneBase(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uimanager) : m_engine(engine), m_uiManager(uimanager) {}
public:
	virtual void begin();

	virtual void OnBegin() abstract;
	virtual void run() abstract;
	virtual void complete();	
	virtual ~SceneBase() {}


	olc::PixelGameEngine&						m_engine; //키보드 마우스 이벤트 가져오기 위해 필요
	olc::QuickGUI::Manager&						m_uiManager;
	std::vector<olc::QuickGUI::BaseControl*>	m_sceneControls; //이 콘트롤들의 포인터들은 엔진이 알아서 지운다.
};

class DefaultScene : public SceneBase
{
public:
	DefaultScene(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uimanager) : SceneBase(engine, uimanager) {}
	void OnBegin() override;
	void run() override;
};