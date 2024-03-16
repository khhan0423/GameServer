#include "pch.h"
#include "GameSessionManager.h"


void GameSessionManager::Add(shared_ptr<GameSession> session)
{
	{
		lock_guard<recursive_mutex> lock(m_lock);
		m_sessionSet.insert(session);
	}
}

void GameSessionManager::Remove(shared_ptr<GameSession> session)
{
	{
		lock_guard<recursive_mutex> lock(m_lock);
		m_sessionSet.erase(session);
	}
}

void GameSessionManager::Broadcast(shared_ptr<SendBuffer> sendBuffer)
{
	{
		lock_guard<recursive_mutex> lock(m_lock);
		for (shared_ptr < GameSession> session : m_sessionSet)
		{
			session->eSEND(sendBuffer);
		}
	}
}
