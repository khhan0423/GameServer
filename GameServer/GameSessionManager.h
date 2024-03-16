#pragma once
#include "SingletonBase.h"
#include "GameSession.h"
#include <set>

#define GetGameSessionManager() GameSessionManager::GetInstance()

class GameSessionManager : public SingletonBase<GameSessionManager>
{
public:
	void Add(shared_ptr<GameSession> session);
	void Remove(shared_ptr<GameSession> session);
	void Broadcast(shared_ptr<SendBuffer> sendBuffer);

private:
	recursive_mutex					_lock;
	set<shared_ptr<GameSession>>	_sessionSet;
};
