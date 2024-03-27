#include "pch.h"
#include "SeneStateChanger.h"
#include "ClientCommonData.h"

void SeneStateChanger::Init()
{
	states[State::eDEFAULT] = new DefaultScene(m_engine, m_uiManager);
	// �ʱ� ���� ����
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
	currentState->SetOnOffLine(ClientGlobalData()->GetONOFFLine());
	currentState->SetAccountID(ClientGlobalData()->GetAccountID());
	
}

void SeneStateChanger::update()
{
	if (currentState != nullptr)
	{
		currentState->run();
	}
}
