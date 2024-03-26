#pragma once
#include "OLCEngine/extensions/olcPGEX_QuickGUI.h"

class SceneBase
{
public:
	SceneBase(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uimanager) : m_engine(engine), m_uiManager(uimanager) {}
public:
	virtual void begin()
	{
		//����� UI���� ���̰� ó���ؾ� �Ѵ�.
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
		//����� UI���� �Ⱥ��̰� ó���ؾ� �Ѵ�.
		for (__int32 cnt = 0; cnt < static_cast<__int32>(m_sceneControls.size()); cnt++)
		{
			if (m_sceneControls[cnt] == nullptr)
				continue;
			m_sceneControls[cnt]->Enable(false);
			m_sceneControls[cnt]->bVisible = false;
		}
	}
	virtual ~SceneBase() {}


	olc::PixelGameEngine&						m_engine; //Ű���� ���콺 �̺�Ʈ �������� ���� �ʿ�
	olc::QuickGUI::Manager&						m_uiManager;
	std::vector<olc::QuickGUI::BaseControl*>	m_sceneControls; //�� ��Ʈ�ѵ��� �����͵��� ������ �˾Ƽ� �����.
};

