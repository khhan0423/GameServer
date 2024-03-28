#pragma once

class GameSession;

class User
{
public:

	unsigned __int64						m_UserId = 0;
	std::string								m_name;
	std::shared_ptr<GameSession>			m_ownerSession;
};