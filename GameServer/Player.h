#pragma once

class GameSession;

class Player
{
public:

	unsigned __int64						m_playerId = 0;
	std::string								m_name;
	std::shared_ptr<GameSession>			m_ownerSession;
};