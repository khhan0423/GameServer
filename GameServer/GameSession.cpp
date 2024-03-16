#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"


void GameSession::OnConnected()
{
	GetGameSessionManager()->Add(static_pointer_cast<GameSession>(shared_from_this()));
	cout << "GameSession::OnConnected()" << endl;
}

void GameSession::OnDisconnected()
{
	GetGameSessionManager()->Remove(static_pointer_cast<GameSession>(shared_from_this()));

	if (m_currentPlayer)
	{
		if (auto _room = m_room.lock())
			_room->RegistTaskLine(&Room::Leave, m_currentPlayer);
	}

	cout << "GameSession::OnDisconnected()" << endl;

	m_currentPlayer = nullptr;
	m_playerList.clear();
}

void GameSession::OnRecvPacket(unsigned char* buffer, __int32 len)
{
	shared_ptr<PacketSession> _session = GetPacketSessionRef();
	PacketHeader* _headerPtr = reinterpret_cast<PacketHeader*>(buffer);

	cout << "GameSession::OnRecvPacket() Len = " << len << endl;

	ClientPacketHandler::HandlePacket(_session, buffer, len);
}

void GameSession::OnSend(__int32 len)
{
	cout << "GameSession::OnSend() Len = " << len << endl;
}