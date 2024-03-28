#pragma once
#include <vector>
#include "LogBase.h"
#include "PacketSession.h"
#include "User.h"

class GameSession : public PacketSession
{
public:
	~GameSession()
	{
		DebugLog("[%s]", __FUNCTION__);
	}

	virtual void							OnConnected() override;
	virtual void							OnDisconnected() override;
	virtual void							OnRecvPacket(unsigned char* buffer, __int32 len) override;
	virtual void							OnSend(__int32 len) override;
public:
	std::vector<std::shared_ptr<User>>	m_playerList;

	std::shared_ptr<User>					m_currentPlayer;//로비서버에서 캐릭터 리스트들 들고있는 용도
};

