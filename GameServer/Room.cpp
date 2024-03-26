#include "pch.h"
#include "Room.h"
#include "Player.h"
#include "GameSession.h"

std::shared_ptr<Room> GRoom = std::make_shared<Room>();

void Room::Enter(std::shared_ptr<Player> player)
{
	m_PlayerMap[player->m_playerId] = player;
	DebugLog("[%s]", __FUNCTION__);
}

void Room::Leave(std::shared_ptr<Player> player)
{
	m_PlayerMap.erase(player->m_playerId);
	DebugLog("[%s]", __FUNCTION__);
}

void Room::Broadcast(std::shared_ptr<SendBuffer> sendBuffer)
{
	for (auto& player : m_PlayerMap)
	{
		std::cout << "Room::Broadcast() -> player->send()" << std::endl;
		DebugLog("[%s]", __FUNCTION__);
	}
}