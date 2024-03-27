#pragma once
#include "OLCEngine/extensions/olcPGEX_QuickGUI.h"
#include "ClientCommonData.h"


//OLCEngine 은 Drawable 객체의 실시간 추가를 허용하지 않는다.
//관리 컨테이너가 락이 안걸려 있다.
//처음에 시작 할 때, 미리 전부 등록해 주고
//UI를 껐다 켰다만 해 주어야 한다.
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


	olc::PixelGameEngine&						m_engine; //키보드 마우스 이벤트 가져오기 위해 필요
	olc::QuickGUI::Manager&						m_uiManager;
	std::vector<olc::QuickGUI::BaseControl*>	m_sceneControls; //이 콘트롤들의 포인터들은 엔진이 알아서 지운다.
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