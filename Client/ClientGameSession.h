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

		//접속이 완료 되었으니 클라이언트 화면을 변경해 주어야 한다.

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