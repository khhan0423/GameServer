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
	// �ٸ� ���µ��� �߰��� �� �ֽ��ϴ�.
};

class SeneStateChanger
{
private:
	std::map<State, SceneBase*> states;
	SceneBase* currentState = nullptr;

	olc::PixelGameEngine& m_engine; //Ű���� ���콺 �̺�Ʈ �������� ���� �ʿ�
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

