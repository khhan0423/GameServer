#include "pch.h"
#include "SceneBase.h"
#include "ClientNetworkSystem.h"
#include "LogBase.h"

void SceneBase::begin()
{
	//����� UI���� ���̰� ó���ؾ� �Ѵ�.
	for (__int32 cnt = 0; cnt < static_cast<__int32>(m_sceneControls.size()); cnt++)
	{
		if (m_sceneControls[cnt] == nullptr)
			continue;
		m_sceneControls[cnt]->Enable(true);
		m_sceneControls[cnt]->bVisible = true;
	}	
}

void SceneBase::complete()
{
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
}

void DefaultScene::Init()
{
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

			olc::QuickGUI::Label* guiTitleScript1 = nullptr;
			guiTitleScript1 = new olc::QuickGUI::Label(m_uiManager,
				"off line", { 0.0f, APP_HEIGHT_DIVIDED_BASE * 0.0f }, { APP_WITDH, APP_HEIGHT_DIVIDED_BASE });
			guiTitleScript1->nAlign = olc::QuickGUI::Label::Alignment::Right;
			m_sceneControls.push_back(guiTitleScript1);

			olc::QuickGUI::Label* guiTitle = nullptr;
			guiTitle = new olc::QuickGUI::Label(m_uiManager,
				"THIS IS DUMMY CLIENT", { 0.0f, APP_HEIGHT_DIVIDED_BASE * 1.0f }, { APP_WITDH, APP_HEIGHT_DIVIDED_BASE * 2 });
			guiTitle->nAlign = olc::QuickGUI::Label::Alignment::Centre;
			guiTitle->bHasBorder = true;
			guiTitle->bHasBackground = true;

			m_sceneControls.push_back(guiTitle);

			olc::QuickGUI::Label* guiTitleScript2 = nullptr;
			guiTitleScript2 = new olc::QuickGUI::Label(m_uiManager,
				"Press 'SPACE' key", { 0.0f, APP_HEIGHT_DIVIDED_BASE * 4.0f }, { APP_WITDH, APP_HEIGHT_DIVIDED_BASE });
			guiTitleScript2->nAlign = olc::QuickGUI::Label::Alignment::Centre;
			m_sceneControls.push_back(guiTitleScript2);

			complete();
		}
	}
}

void DefaultScene::run()
{
	if (m_engine.GetKey(olc::SPACE).bReleased)
	{
		if (m_isProcessConnecting == false)
		{
			NetworkSystem()->StartConnect();
			m_isProcessConnecting.exchange(true);
		}		
	}
}
