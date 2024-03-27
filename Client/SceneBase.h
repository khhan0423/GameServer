#pragma once
#include "OLCEngine/extensions/olcPGEX_QuickGUI.h"
#include "ClientCommonData.h"


//OLCEngine �� Drawable ��ü�� �ǽð� �߰��� ������� �ʴ´�.
//���� �����̳ʰ� ���� �Ȱɷ� �ִ�.
//ó���� ���� �� ��, �̸� ���� ����� �ְ�
//UI�� ���� �״ٸ� �� �־�� �Ѵ�.
class SceneBase
{
protected:
	olc::QuickGUI::Label* guiOnOffline = nullptr;
	olc::QuickGUI::Label* guiAccountID = nullptr;
public:
	void SetOnOffLine(const std::string& _state) { if (guiOnOffline != nullptr) guiOnOffline->sText = _state; }
	void SetAccountID(const std::string& _accountID) { if (guiAccountID != nullptr) guiAccountID->sText = _accountID; }
public:
	SceneBase(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uimanager) : m_engine(engine), m_uiManager(uimanager) 
	{

	}
public:
	virtual void begin();

	virtual void Init()abstract;
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
	DefaultScene(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uimanager) : SceneBase(engine, uimanager) 
	{
		Init();
	}
	~DefaultScene() { m_isProcessConnecting, m_isProcessConnecting.exchange(false); }
	void Init() override;
	void run() override;
	std::atomic<bool>	m_isProcessConnecting = false;
};