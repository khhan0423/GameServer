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

		//접속이 완료 되었으니 클라이언트 화변을 변경해 주어야 한다.
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