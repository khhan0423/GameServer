#pragma once
#include <map>
#include "TaskQueue.h"
#include "SendBuffer.h"

class Player;

class Room : public TaskQueue
{
public:
	void Enter(shared_ptr<Player> player);
	void Leave(shared_ptr<Player> player);
	void Broadcast(shared_ptr<SendBuffer> sendBuffer);

private:
	map<unsigned __int64, shared_ptr<Player>>	m_PlayerMap;;
};

extern shared_ptr<Room> GRoom;

