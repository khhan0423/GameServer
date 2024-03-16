#include "pch.h"
#include "ServerPacketHandler.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len)
{
	PacketHeader* _header = reinterpret_cast<PacketHeader*>(buffer);
	// TODO : Log
	return false;
}