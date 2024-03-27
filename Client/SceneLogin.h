#pragma once
#include "SceneBase.h"
#include "Protocol/ProtocolClientToServerEnum.pb.h"
#include "Protocol/ProtocolClientToServer.pb.h"
#include "ServerPacketHandler.h"
#include "ClientNetworkSystem.h"
#include "ClientCommonData.h"

class SceneLogin : public SceneBase
{
protected:
	olc::QuickGUI::TextBox* m_textBoxID = nullptr;
	olc::QuickGUI::Button*	m_guiLoginButton = nullptr;
	std::atomic<bool>		m_IsProcessLogin = false;
	
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

			olc::QuickGUI::Label* guiTextBoxScript = nullptr;
			guiTextBoxScript = new olc::QuickGUI::Label(m_uiManager,
				"ID:", { APP_WIDTH_DIVIDED_BASE * 1.0f, APP_HEIGHT_DIVIDED_BASE * 3.0f }, { APP_WIDTH_DIVIDED_BASE, (APP_HEIGHT_DIVIDED_BASE / 2.0f) });
			guiTextBoxScript->nAlign = olc::QuickGUI::Label::Alignment::Centre;

			m_sceneControls.push_back(guiTextBoxScript);

			m_textBoxID = new olc::QuickGUI::TextBox(m_uiManager,
				"", { APP_WIDTH_DIVIDED_BASE * 2.0f, APP_HEIGHT_DIVIDED_BASE * 3.0f}, { APP_WIDTH_DIVIDED_BASE * 2.0f, (APP_HEIGHT_DIVIDED_BASE / 2.0f) });

			m_sceneControls.push_back(m_textBoxID);

			m_guiLoginButton = new olc::QuickGUI::Button(m_uiManager,
				"LOGIN", { APP_WIDTH_DIVIDED_BASE * 2.0f, (APP_HEIGHT_DIVIDED_BASE * 4.0f) }, { APP_WIDTH_DIVIDED_BASE * 1.0f, (APP_HEIGHT_DIVIDED_BASE / 2.0f) });

			m_sceneControls.push_back(m_guiLoginButton);

			complete();
		}

		

	}
	void run() override
	{
		if (m_guiLoginButton->bReleased)
		{
			if (m_IsProcessLogin == false)
			{
				std::string _id = m_textBoxID->sText;
				ProtocolClientToServer::RequestLogin _ReqLogin;
				_ReqLogin.set_m_accountid(_id);
				auto _sendBuffer = ServerPacketHandler::MakeSendBuffer(_ReqLogin);
				NetworkSystem()->Send(_sendBuffer);
				ClientGlobalData()->m_AccountID = StringUtil::Utf8ToWide(_id);
				m_IsProcessLogin.exchange(true);
			}
		}
	}
};