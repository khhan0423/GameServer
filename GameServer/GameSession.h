#pragma once
#include <vector>
#include "LogBase.h"
#include "PacketSession.h"
#include "Player.h"
#include "Room.h"

class GameSession : public PacketSession
{
public:
	~GameSession()
	{
		DebugLog("[%s]", __FUNCTION__);
	}

	virtual void						OnConnected() override;
	virtual void						OnDisconnected() override;
	virtual void						OnRecvPacket(unsigned char* buffer, __int32 len) override;
	virtual void						OnSend(__int32 len) override;

	void								SetSessionGUID(const unsigned __int64 key) { m_GUID = key; }
	unsigned __int64					GetSessionGUID() { return m_GUID; }
public:
	vector<shared_ptr<Player>>			m_playerList;

	shared_ptr<Player>					m_currentPlayer;//�κ񼭹����� ĳ���� ����Ʈ�� ����ִ� �뵵
	weak_ptr<class Room>				m_room; //���� ���� ���� �ְ� ���� ���� ������, ��ũ������
private:
	unsigned __int64					m_GUID = 0;
};

