#pragma once
#include "SingletonBase.h"
#include "GameSession.h"
#include <set>

#define GetGameSessionManager() GameSessionManager::GetInstance()

//LTS ������ ������ �����ϴ� MAP�� �ξ,
//���� ������θ� IOó���� �ϵ��� �ϸ�, 
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
