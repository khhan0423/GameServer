#pragma once
#include <vector>
#include "PacketSession.h"
#include "Player.h"
#include "Room.h"

class GameSession : public PacketSession
{
public:
	~GameSession()
	{
		cout << "~GameSession" << endl;
	}

	virtual void						OnConnected() override;
	virtual void						OnDisconnected() override;
	virtual void						OnRecvPacket(unsigned char* buffer, __int32 len) override;
	virtual void						OnSend(__int32 len) override;

public:
	vector<shared_ptr<Player>>			m_playerList;

	shared_ptr<Player>					m_currentPlayer;//로비서버에서 캐릭터 리스트들 들고있는 용도
	weak_ptr<class Room>				m_room; //룸이 있을 수도 있고 없을 수도 있으니, 위크포인터
};

