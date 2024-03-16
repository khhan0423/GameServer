#pragma once
#include "PacketSession.h"

using PacketHandlerFunc = std::function<bool(shared_ptr<PacketSession>&, unsigned char*, __int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

enum : __int32
{
	//Packet ID enum
};

// Custom Handlers
bool Handle_INVALID(shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len);


class ClientPacketHandler
{
public:
	static void Init()
	{
		for (__int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;
	}

	static bool HandlePacket(shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->m_protocolID](session, buffer, len);
	}

private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, shared_ptr<PacketSession>&, unsigned char*, __int32& session, BYTE* buffer, __int32 len)
	{
		PacketType _pkt;
		if (_pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(session, _pkt);
	}

	template<typename T>
	static shared_ptr<SendBuffer> MakeSendBuffer(T& pkt, __int32 pktId)
	{
		const unsigned __int16	_dataSize = static_cast<unsigned __int16>(pkt.ByteSizeLong());
		const unsigned __int16	_packetSize = _dataSize + sizeof(PacketHeader);

		shared_ptr<SendBuffer> _sendBuffer = make_shared<SendBuffer>(_packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_sendBuffer->Buffer());
		header->m_size = _packetSize;
		header->m_protocolID = pktId;
		VERIFY(pkt.SerializeToArray(&header[1], _dataSize));
		_sendBuffer->Close(_packetSize);

		return _sendBuffer;
	}
};

