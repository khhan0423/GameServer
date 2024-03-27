#pragma once
#include "SceneBase.h"
#include "DummyClient.h"
#include "ClientNetworkSystem.h"
#include "ClientCommonData.h"

class SceneIntro : public SceneBase
{
protected:
	olc::QuickGUI::Button* m_guiLoginButton = nullptr;
	olc::QuickGUI::Button* guiEXITButton = nullptr;

public:
	SceneIntro(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uimanager) : SceneBase(engine, uimanager) 
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

			std::string _onOffLine = ClientGlobalData()->GetONOFFLine();
			guiOnOffline = new olc::QuickGUI::Label(m_uiManager,
				_onOffLine, { 0.0f, APP_HEIGHT_DIVIDED_BASE * 0.0f }, { APP_WITDH, APP_HEIGHT_DIVIDED_BASE });
			guiOnOffline->nAlign = olc::QuickGUI::Label::Alignment::Right;

			m_sceneControls.push_back(guiOnOffline);

			olc::QuickGUI::Label* guiTitle = nullptr;
			guiTitle = new olc::QuickGUI::Label(m_uiManager,
				"THIS IS DUMMY CLIENT", { 0.0f, APP_HEIGHT_DIVIDED_BASE * 1.0f }, { APP_WITDH, APP_HEIGHT_DIVIDED_BASE * 2 });
			guiTitle->nAlign = olc::QuickGUI::Label::Alignment::Centre;
			guiTitle->bHasBorder = true;
			guiTitle->bHasBackground = true;

			m_sceneControls.push_back(guiTitle);

			//로그인
			
			m_guiLoginButton = new olc::QuickGUI::Button(m_uiManager,
				"LOGIN", { APP_WIDTH_DIVIDED_BASE * 2.0f, (APP_HEIGHT_DIVIDED_BASE * 4.0f) }, { APP_WIDTH_DIVIDED_BASE * 1.0f, (APP_HEIGHT_DIVIDED_BASE / 2.0f) });

			m_sceneControls.push_back(m_guiLoginButton);

			//끝내기			
			guiEXITButton = new olc::QuickGUI::Button(m_uiManager,
				"EXIT", { APP_WIDTH_DIVIDED_BASE * 2.0f, (APP_HEIGHT_DIVIDED_BASE * 4.0f) + (APP_HEIGHT_DIVIDED_BASE / 2.0f) }, { APP_WIDTH_DIVIDED_BASE * 1.0f, (APP_HEIGHT_DIVIDED_BASE / 2.0f) });

			m_sceneControls.push_back(guiEXITButton);

			complete();
		}
	}

	void run() override
	{
		if (m_guiLoginButton->bReleased)
		{
			ClinetSystem()->m_SceneChanger->transition(State::eLOGIN);
		}

		if (guiEXITButton->bReleased)
		{
			m_engine.olc_shutDown();
			::ExitProcess(0);
		}
	}
};

