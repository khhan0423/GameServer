#pragma once
#include "Protocol/ProtocolServerToClientEnum.pb.h"
#include "Protocol/ProtocolServerToClient.pb.h"


#include "Protocol/ProtocolClientToServerEnum.pb.h"
#include "Protocol/ProtocolClientToServer.pb.h"

#include "PacketSession.h"

using PacketHandlerFunc = std::function<bool(std::shared_ptr<PacketSession>&, unsigned char*, __int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

// Custom Handlers
bool Handle_INVALID(std::shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len);
bool Handle_RequestLogin(std::shared_ptr<PacketSession>& session, ProtocolClientToServer::RequestLogin& pkt);

class ClientPacketHandler
{
public:
	static void Init()
	{
		for (__int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;

		GPacketHandler[ProtocolClientToServer::PacketType::eREQUEST_LOGIN] = [](std::shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len) { return HandlePacket<ProtocolClientToServer::RequestLogin>(Handle_RequestLogin, session, buffer, len); };
	}

	static bool HandlePacket(std::shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->m_protocolID](session, buffer, len);
	}

	//Server -> Client
	static std::shared_ptr<SendBuffer> MakeSendBuffer(ProtocolServerToClient::ResultLogin& pkt) { return MakeSendBuffer(pkt, ProtocolServerToClient::PacketType::eRESULT_LOGIN); }

private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, std::shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len)
	{
		PacketType pkt;
		if (pkt.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(session, pkt);
	}

	template<typename T>
	static std::shared_ptr<SendBuffer> MakeSendBuffer(T& pkt, __int32 pktId)
	{
		const unsigned __int16	_dataSize = static_cast<unsigned __int16>(pkt.ByteSizeLong());
		const unsigned __int16	_packetSize = _dataSize + sizeof(PacketHeader);

		std::shared_ptr<SendBuffer> _sendBuffer = std::make_shared<SendBuffer>(_packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_sendBuffer->GetBuffer());
		header->m_size = _packetSize;
		header->m_protocolID = pktId;
		VERIFY(pkt.SerializeToArray(&header[1], _dataSize));
		//send버퍼의 버퍼 주소로 직접 write 하는 경우는 send 버퍼 close 꼭 해야함. 
		_sendBuffer->Close(_packetSize);

		return _sendBuffer;
	}
};

