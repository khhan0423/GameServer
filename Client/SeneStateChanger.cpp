#include "pch.h"
#include "SeneStateChanger.h"

void SeneStateChanger::Init()
{
	states[State::eDEFAULT] = new DefaultScene(m_engine, m_uiManager);
	// 초기 상태 설정
	transition(State::eDEFAULT);
}

void SeneStateChanger::RegistState(State state, SceneBase* stateObject)
{
	states.emplace(std::make_pair(state, stateObject));
}

void SeneStateChanger::transition(State newState)
{
	if (currentState != nullptr)
	{
		currentState->complete();
	}
	currentState = states[newState];
	currentState->begin();
}

void SeneStateChanger::update()
{
	if (currentState != nullptr)
	{
		currentState->run();
	}
}
