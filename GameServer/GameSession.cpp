#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"
#include "ClientPacketHandler.h"


void GameSession::OnConnected()
{
	GetGameSessionManager()->Add(std::static_pointer_cast<GameSession>(shared_from_this()));
	DebugLog("[%s]", __FUNCTION__);
}

void GameSession::OnDisconnected()
{
	GetGameSessionManager()->Remove(std::static_pointer_cast<GameSession>(shared_from_this()));

	DebugLog("[%s]", __FUNCTION__);

	m_currentPlayer = nullptr;
	m_playerList.clear();
}

void GameSession::OnRecvPacket(unsigned char* buffer, __int32 len)
{
	std::shared_ptr<PacketSession> _session = GetPacketSessionRef();
	PacketHeader* _headerPtr = reinterpret_cast<PacketHeader*>(buffer);

	DebugLog("[%s] len[%d] :", __FUNCTION__, len);

	ClientPacketHandler::HandlePacket(_session, buffer, len);
}

void GameSession::OnSend(__int32 len)
{
	DebugLog("[%s]", __FUNCTION__);
}