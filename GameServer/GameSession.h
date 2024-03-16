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

	shared_ptr<Player>					m_currentPlayer;//�κ񼭹����� ĳ���� ����Ʈ�� ����ִ� �뵵
	weak_ptr<class Room>				m_room; //���� ���� ���� �ְ� ���� ���� ������, ��ũ������
};

