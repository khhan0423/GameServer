#include "pch.h"
#include "LogBase.h"
#include "ServerPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len)
{
	DebugLog("[%s]", __FUNCTION__);
	PacketHeader* _header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}

bool Handle_ResultLogin(shared_ptr<PacketSession>& session, ProtocolServerToClient::ResultLogin& pkt)
{

	return true;
}


