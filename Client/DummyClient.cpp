#include "pch.h"
#include "DummyClient.h"

void DummyClient::Init()
{
	m_SceneChanger = new SeneStateChanger(*this, guiManager);
	//m_SceneChanger->RegistState(State::eINTRO, new Intro(*this, guiManager));
	//m_SceneChanger->RegistState(State::eMAINSCENE, new MainScene(*this, guiManager));
}

bool DummyClient::OnUserCreate()
{
	return true;
}	

bool DummyClient::OnUserUpdate(float fElapsedTime) 
{
	m_SceneChanger->update();
	guiManager.Update(this);

	Clear(olc::BLACK);
	guiManager.Draw(this);

	return true;
}
