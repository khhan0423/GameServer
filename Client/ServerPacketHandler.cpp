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


