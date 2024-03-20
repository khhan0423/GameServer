#include "pch.h"
#include "GameSessionManager.h"


void GameSessionManager::Add(shared_ptr<GameSession> session)
{
	{
		lock_guard<recursive_mutex> lock(m_lock);
		m_sessionSet.insert(session);
		SystemLog("[%s] insert session manager - key : [%lld]", __FUNCTION__, session->m_currentPlayer);
	}
	DebugLog("[%s]", __FUNCTION__);
}

void GameSessionManager::Remove(shared_ptr<GameSession> session)
{
	{
		lock_guard<recursive_mutex> lock(m_lock);
		m_sessionSet.erase(session);		
	}
	DebugLog("[%s]", __FUNCTION__);
}

void GameSessionManager::Broadcast(shared_ptr<SendBuffer> sendBuffer)
{
	{
		lock_guard<recursive_mutex> lock(m_lock);
		for (shared_ptr < GameSession> session : m_sessionSet)
		{
			session->Send(sendBuffer);			
		}
		DebugLog("[%s]", __FUNCTION__);
	}
}
