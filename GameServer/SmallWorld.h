#pragma once
#include <map>
#include "TaskQueue.h"
#include "SendBuffer.h"

class User;

class SmallWorld : public TaskQueue
{
public:
	void Enter(std::shared_ptr<User> playerShared);
	void Leave(std::shared_ptr<User> playerShared);
	void Broadcast(std::shared_ptr<SendBuffer> sendBuffer);

private:
	std::map<unsigned __int64, std::shared_ptr<User>>	m_UserMap;;
};

extern std::shared_ptr<SmallWorld> GRoom;

