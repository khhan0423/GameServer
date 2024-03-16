#pragma once

class GameSession;

class Player
{
public:

	unsigned __int64					m_playerId = 0;
	string								m_name;
	shared_ptr<GameSession>				m_ownerSession;
};