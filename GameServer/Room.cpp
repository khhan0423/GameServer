#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "GameSession.h"

shared_ptr<Room> GRoom = make_shared<Room>();

void Room::Enter(shared_ptr<Player> player)
{
	m_PlayerMap[player->m_playerId] = player;
	cout << "Room::Enter()" << endl;
}

void Room::Leave(shared_ptr<Player> player)
{
	m_PlayerMap.erase(player->m_playerId);
	cout << "Room::Leave()" << endl;
}

void Room::Broadcast(shared_ptr<SendBuffer> sendBuffer)
{
	for (auto& player : m_PlayerMap)
	{
		cout << "Room::Broadcast() -> player->send()" << endl;
		player.second->m_ownerSession->Send(sendBuffer);
	}
}