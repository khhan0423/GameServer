#pragma once
#include "PacketSession.h"
#include "Protocol/ProtocolServerToClientEnum.pb.h"
#include "Protocol/ProtocolServerToClient.pb.h"


#include "Protocol/ProtocolClientToServerEnum.pb.h"
#include "Protocol/ProtocolClientToServer.pb.h"


using PacketHandlerFunc = std::function<bool(std::shared_ptr<PacketSession>&, unsigned char*, __int32)>;
extern PacketHandlerFunc GPacketHandler[UINT16_MAX];

// Custom Handlers
bool Handle_INVALID(std::shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len);
bool Handle_ResultLogin(std::shared_ptr<PacketSession>& session, ProtocolServerToClient::ResultLogin& pkt);
bool Handle_ResultCreateAcount(std::shared_ptr<PacketSession>& session, ProtocolServerToClient::ResultCreateAccount& pkt);

class ServerPacketHandler
{
public:
	static void Init()
	{
		for (__int32 i = 0; i < UINT16_MAX; i++)
			GPacketHandler[i] = Handle_INVALID;		
		
		GPacketHandler[ProtocolServerToClient::PacketType::eRESULT_LOGIN] = [](std::shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len) { return HandlePacket<ProtocolServerToClient::ResultLogin>(Handle_ResultLogin, session, buffer, len); };
		GPacketHandler[ProtocolServerToClient::PacketType::eRESULT_CREATE_ACCOUNT] = [](std::shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len) { return HandlePacket<ProtocolServerToClient::ResultCreateAccount>(Handle_ResultCreateAcount, session, buffer, len); };
	}

	static bool HandlePacket(std::shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len)
	{
		PacketHeader* header = reinterpret_cast<PacketHeader*>(buffer);
		return GPacketHandler[header->m_protocolID](session, buffer, len);
	}

	//Client -> Server
	static std::shared_ptr<SendBuffer> MakeSendBuffer(ProtocolClientToServer::RequestLogin& pkt) { return MakeSendBuffer(pkt, ProtocolClientToServer::PacketType::eREQUEST_LOGIN); }
	static std::shared_ptr<SendBuffer> MakeSendBuffer(ProtocolClientToServer::RequestCreateAccount& pkt) { return MakeSendBuffer(pkt, ProtocolClientToServer::PacketType::eREQUEST_CREATE_ACCOUNT); }

private:
	template<typename PacketType, typename ProcessFunc>
	static bool HandlePacket(ProcessFunc func, std::shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len)
	{
		PacketType _packetType;
		if (_packetType.ParseFromArray(buffer + sizeof(PacketHeader), len - sizeof(PacketHeader)) == false)
			return false;

		return func(session, _packetType);
	}

	template<typename T>
	static std::shared_ptr<SendBuffer> MakeSendBuffer(T& packetType, __int32 packetID)
	{
		const unsigned __int16	_dataSize = static_cast<unsigned __int16>(packetType.ByteSizeLong());
		const unsigned __int16	_packetSize = _dataSize + sizeof(PacketHeader);

		std::shared_ptr<SendBuffer> _sendBuffer = std::make_shared<SendBuffer>(_packetSize);
		PacketHeader* header = reinterpret_cast<PacketHeader*>(_sendBuffer->GetBuffer());
		header->m_size = _packetSize;
		header->m_protocolID = packetID;
		VERIFY(packetType.SerializeToArray(&header[1], _dataSize));
		//send������ ���� �ּҷ� ���� write �ϴ� ���״� send ���� close �� �ؾ���.
		_sendBuffer->Close(_packetSize);

		return _sendBuffer;
	}
};

