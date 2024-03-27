#pragma once
#include <map>
#include "SceneBase.h"


class DefaultScene;
enum class State
{
	eDEFAULT,
	eINTRO,
	eLOGIN,
	eWELCOME,
	eCREATEACCOUNT,
	// 다른 상태들을 추가할 수 있습니다.
};

class SeneStateChanger
{
private:
	std::map<State, SceneBase*> states;
	SceneBase* currentState = nullptr;

	olc::PixelGameEngine& m_engine; //키보드 마우스 이벤트 가져오기 위해 필요
	olc::QuickGUI::Manager& m_uiManager;
public:
	SeneStateChanger(olc::PixelGameEngine& engine, olc::QuickGUI::Manager& uiManager) : m_engine(engine), m_uiManager(uiManager)
	{
		Init();
	}

	void Init();
	void RegistState(State state, SceneBase* stateObject);
	void transition(State newState);
	void update();
};

