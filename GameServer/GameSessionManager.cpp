#include "pch.h"
#include "GameSessionManager.h"


void GameSessionManager::Add(shared_ptr<GameSession> session)
{
	{
		lock_guard<recursive_mutex> lock(_lock);
		_sessionSet.insert(session);
	}
}

void GameSessionManager::Remove(shared_ptr<GameSession> session)
{
	{
		lock_guard<recursive_mutex> lock(_lock);
		_sessionSet.erase(session);
	}
}

void GameSessionManager::Broadcast(shared_ptr<SendBuffer> sendBuffer)
{
	{
		lock_guard<recursive_mutex> lock(_lock);
		for (shared_ptr < GameSession> session : _sessionSet)
		{
			session->Send(sendBuffer);
		}
	}
}
