#pragma once
#include "SceneBase.h"

class SceneLogin : public SceneBase
{
public:
	SceneLogin(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uimanager) : SceneBase(engine, uimanager) 
	{
		Init();
	}
	void Init() override
	{
		if (m_sceneControls.empty() == true)
		{
			//처음 실행
			//이 씬에서 사용할 UI등록및 초기화 작업			
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

			complete();
		}

	}
	void run() override
	{

	}
};