#pragma once
#include "SceneBase.h"
#include "ClientCommonData.h"
#include "StringUtil.h"

class SceneCreateAccount : public SceneBase
{
protected:

public:
	SceneCreateAccount(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uimanager) : SceneBase(engine, uimanager)
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
				"THIS IS DUMMY CLIENT", { 0.0f, APP_HEIGHT_DIVIDED_BASE * 1.0f }, { APP_WITDH, APP_HEIGHT_DIVIDED_BASE });
			guiTitle->nAlign = olc::QuickGUI::Label::Alignment::Centre;
			guiTitle->bHasBorder = true;
			guiTitle->bHasBackground = true;

			m_sceneControls.push_back(guiTitle);

			olc::QuickGUI::Label* guiWelcomeText = nullptr;
			guiWelcomeText = new olc::QuickGUI::Label(m_uiManager,
				"WELCOME", { 0.0f, APP_HEIGHT_DIVIDED_BASE * 2.0f }, { APP_WITDH, APP_HEIGHT_DIVIDED_BASE });
			guiWelcomeText->nAlign = olc::QuickGUI::Label::Alignment::Centre;

			m_sceneControls.push_back(guiWelcomeText);

			std::string _accountID = StringUtil::WideToUtf8(ClientGlobalData()->m_AccountID);
			guiAccountID = new olc::QuickGUI::Label(m_uiManager,
				"user", { 0.0f, APP_HEIGHT_DIVIDED_BASE * 3.0f }, { APP_WITDH, APP_HEIGHT_DIVIDED_BASE });
			guiAccountID->nAlign = olc::QuickGUI::Label::Alignment::Centre;

			m_sceneControls.push_back(guiAccountID);

			complete();
		}

	}
	void run() override
	{

	}
};