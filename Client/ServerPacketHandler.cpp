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
			//������ ���� ��� ���� ���� ȭ������ ȭ�� ���� ��ȯ
			ClinetSystem()->m_SceneChanger->transition(State::eCREATEACCOUNT);
		}
		else
		{
			//�̹� ������ �ִ� ���
			//ȯ�� ȭ������ ��ȯ
			ClinetSystem()->m_SceneChanger->transition(State::eWELCOME);
		}
	}


	return true;
}

bool Handle_ResultCreateAcount(std::shared_ptr<PacketSession>& session, ProtocolServerToClient::ResultCreateAccount& pkt)
{
	bool _result = pkt.m_success();
	DebugLog("[%s] result :%d", __FUNCTION__, _result);

	if (_result == true)
	{
		ClinetSystem()->m_SceneChanger->transition(State::eWELCOME);
	}

	return true;
}

