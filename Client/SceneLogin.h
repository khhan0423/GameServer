#pragma once
#include "SceneBase.h"

class SceneLogin : public SceneBase
{
public:
	SceneLogin(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uimanager) : SceneBase(engine, uimanager) {}
	void OnBegin() override
	{
		if (m_sceneControls.empty() == true)
		{
			//ó�� ����
			//�� ������ ����� UI��Ϲ� �ʱ�ȭ �۾�			
			//--------------------------------------0
			//
			//--------------------------------------1
			//
			//--------------------------------------2
			//
			//--------------------------------------3
			// 
			//--------------------------------------4
			// 
			//--------------------------------------5
			// 
			//--------------------------------------6
		}

	}
	void run() override
	{

	}
};