#include "pch.h"
#include "GameSession.h"
#include "GameSessionManager.h"

void GameSession::OnConnected()
{
	GetGameSessionManager()->Add(static_pointer_cast<GameSession>(shared_from_this()));
}

void GameSession::OnDisconnected()
{
	GetGameSessionManager()->Remove(static_pointer_cast<GameSession>(shared_from_this()));
}

__int32 GameSession::OnRecv(BYTE* buffer, __int32 len)
{
	cout << "OnRecv Len = " << len << endl;

	shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(4096);
	sendBuffer->CopyData(buffer, len);

	GetGameSessionManager()->Broadcast(sendBuffer);

	return len;
}

void GameSession::OnSend(__int32 len)
{
	cout << "OnSend Len = " << len << endl;
}