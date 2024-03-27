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


	olc::PixelGameEngine&						m_engine; //Ű���� ���콺 �̺�Ʈ �������� ���� �ʿ�
	olc::QuickGUI::Manager&						m_uiManager;
	std::vector<olc::QuickGUI::BaseControl*>	m_sceneControls; //�� ��Ʈ�ѵ��� �����͵��� ������ �˾Ƽ� �����.
};

class DefaultScene : public SceneBase
{
public:
	DefaultScene(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uimanager) : SceneBase(engine, uimanager) {}
	void OnBegin() override;
	void run() override;
};