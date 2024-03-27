#include "pch.h"
#include "DummyClient.h"
#include "SceneIntro.h"
#include "SceneLogin.h"

void DummyClient::Init()
{
	m_SceneChanger = new SeneStateChanger(*this, guiManager);
	m_SceneChanger->RegistState(State::eINTRO, new SceneIntro(*this, guiManager));
	m_SceneChanger->RegistState(State::eLOGIN, new SceneLogin(*this, guiManager));
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
