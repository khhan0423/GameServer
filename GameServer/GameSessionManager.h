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
	void Add(shared_ptr<GameSession> session);
	void Remove(shared_ptr<GameSession> session);
	void Broadcast(shared_ptr<SendBuffer> sendBuffer);

private:
	recursive_mutex					m_lock;
	set<shared_ptr<GameSession>>	m_sessionSet;
};
