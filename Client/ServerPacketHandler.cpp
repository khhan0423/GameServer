#include "pch.h"
#include "LogBase.h"
#include "ServerPacketHandler.h"
#include "DummyClient.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(std::shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len)
{
	PacketHeader* _header = reinterpret_cast<PacketHeader*>(buffer);
	DebugLog("[%s] INVALID PACKET", __FUNCTION__);
	return false;
}

bool Handle_ResultLogin(std::shared_ptr<PacketSession>& session, ProtocolServerToClient::ResultLogin& pkt)
{
	bool _result = pkt.m_success();
	__int32 _rowCount = pkt.m_playercount();
	DebugLog("[%s] result :%d playercount : %d", __FUNCTION__, _result, _rowCount);

	if (_result == true)
	{
		if (_rowCount == 0)
		{
			//계정이 없는 경우 계정 생성 화면으로 화면 상태 전환
		}
		else
		{
			//이미 계정이 있는 경우
			//환영 화면으로 전환
			ClinetSystem()->m_SceneChanger->transition(State::eWELCOME);
		}
	}


	return true;
}


