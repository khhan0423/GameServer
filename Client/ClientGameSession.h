#pragma once
#include "PacketSession.h"
#include "ServerPacketHandler.h"
#include "Protocol/ProtocolClientToServer.pb.h"
#include "SceneBase.h"
#include "DummyClient.h"

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
		ClinetSystem()->m_SceneChanger->transition(State::eINTRO);

		//ProtocolServerToClient::ResultLogin -> server

//		ProtocolClientToServer::RequestLogin _ReqLogin;
//		_ReqLogin.set_m_accountid("khhan0423");
//		auto _sendBuffer = ServerPacketHandler::MakeSendBuffer(_ReqLogin);
//		Send(_sendBuffer);
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
	}
};