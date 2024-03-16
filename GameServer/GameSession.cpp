#include "pch.h"
#include "GameSession.h"

void GameSession::OnConnected()
{
	//GSessionManager.Add(static_pointer_cast<GameSession>(shared_from_this()));
}

void GameSession::OnDisconnected()
{
	//GSessionManager.Remove(static_pointer_cast<GameSession>(shared_from_this()));
}

__int32 GameSession::OnRecv(BYTE* buffer, __int32 len)
{
	// Echo
	cout << "OnRecv Len = " << len << endl;

	shared_ptr<SendBuffer> sendBuffer = make_shared<SendBuffer>(4096);
	sendBuffer->CopyData(buffer, len);

	//GSessionManager.Broadcast(sendBuffer);

	return len;
}

void GameSession::OnSend(__int32 len)
{
	cout << "OnSend Len = " << len << endl;
}