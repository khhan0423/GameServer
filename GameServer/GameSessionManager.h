#pragma once
#include "SingletonBase.h"
#include "GameSession.h"
#include <set>

#define GetGameSessionManager() GameSessionManager::GetInstance()

//LTS 영역에 세션을 관리하는 MAP을 두어서,
//같은 쓰레드로만 IO처리를 하도록 하면, 
class GameSessionManager : public TSingletonBase<GameSessionManager>
{
public:
	void Add(std::shared_ptr<GameSession> session);
	void Remove(std::shared_ptr<GameSession> session);
	void Broadcast(std::shared_ptr<SendBuffer> sendBuffer);

private:
	std::recursive_mutex					m_lock;
	std::set<std::shared_ptr<GameSession>>	m_sessionSet;
};
