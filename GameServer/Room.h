#pragma once
#include <map>
#include "TaskQueue.h"
#include "SendBuffer.h"

class Player;

class Room : public TaskQueue
{
public:
	void Enter(std::shared_ptr<Player> player);
	void Leave(std::shared_ptr<Player> player);
	void Broadcast(std::shared_ptr<SendBuffer> sendBuffer);

private:
	std::map<unsigned __int64, std::shared_ptr<Player>>	m_PlayerMap;;
};

extern std::shared_ptr<Room> GRoom;

