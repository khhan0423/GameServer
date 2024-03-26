#include "pch.h"
#include "SeqIDGenerator.h"
#include "GameSessionManager.h"


void GameSessionManager::Add(std::shared_ptr<GameSession> session)
{
	{
		std::lock_guard<std::recursive_mutex> lock(m_lock);
		m_sessionSet.insert(session);
		session->SetSessionGUID(SessionGUIDGen()->Generate());
		SystemLog("[%s] insert session manager - key : [%lld]", __FUNCTION__, session->m_currentPlayer);
	}
	DebugLog("[%s]", __FUNCTION__);
}

void GameSessionManager::Remove(std::shared_ptr<GameSession> session)
{
	{
		std::lock_guard<std::recursive_mutex> lock(m_lock);
		m_sessionSet.erase(session);		
	}
	DebugLog("[%s]", __FUNCTION__);
}

void GameSessionManager::Broadcast(std::shared_ptr<SendBuffer> sendBuffer)
{
	{
		std::lock_guard<std::recursive_mutex> lock(m_lock);
		for (std::shared_ptr < GameSession> session : m_sessionSet)
		{
			session->Send(sendBuffer);			
		}
		DebugLog("[%s]", __FUNCTION__);
	}
}
