#include "pch.h"
#include "GameServerSystem.h"

GameServerSystem::GameServerSystem()
{
	Initialize();
}

bool GameServerSystem::Initialize()
{
	//do loadwise thins.. 
}

void GameServerSystem::Release()
{
	//do release and delete dynamic resources.
}
 
void GameServerSystem::Intiate() 
{
	//ServerService init and start.
}

void GameServerSystem::Run()
{
	//if Intiate process not finish, do not Run.
	//using m_isReady flag value.
}

void GameServerSystem::CheckAnotherServers()
{
	//to - do
	//for hear bear with another servers.
}
