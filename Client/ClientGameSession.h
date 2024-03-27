#pragma once
#include "PacketSession.h"
#include "ServerPacketHandler.h"
#include "Protocol/ProtocolClientToServer.pb.h"
#include "SceneBase.h"
#include "DummyClient.h"
#include "ClientCommonData.h"

class ClientGameSession : public PacketSession
{
public:
	~ClientGameSession()
	{
		DebugLog("[%s]", __FUNCTION__);
	}

	virtual void OnConnected() override
	{
		DebugLog("[%s]", __FUNCTION__);

		//������ �Ϸ� �Ǿ����� Ŭ���̾�Ʈ ȭ���� ������ �־�� �Ѵ�.

		ClientGlobalData()->m_isConnected.exchange(true);
		ClinetSystem()->m_SceneChanger->transition(State::eINTRO);
	}

	virtual void OnRecvPacket(unsigned char* buffer, __int32 len) override
	{
		std::shared_ptr<PacketSession> _session = GetPacketSessionRef();
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);

		DebugLog("[%s] len : ", __FUNCTION__, len);

		ServerPacketHandler::HandlePacket(_session, buffer, len);
	}

	virtual void OnSend(__int32 len) override
	{
		DebugLog("[%s] len : ", __FUNCTION__, len);
	}

	virtual void OnDisconnected() override
	{
		DebugLog("[%s]", __FUNCTION__);
		ClientGlobalData()->m_isConnected.exchange(false);
	}
};