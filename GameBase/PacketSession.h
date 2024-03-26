#pragma once
#include "Session.h"

struct PacketHeader
{
	unsigned __int16 m_size;
	unsigned __int32 m_protocolID;
};

class PacketSession : public Session
{
public:
	PacketSession();
	virtual ~PacketSession();

	std::shared_ptr<PacketSession>	GetPacketSessionRef() { return std::static_pointer_cast<PacketSession>(shared_from_this()); }

protected:
	//PacketSession �� ��ӹ޴� Ŭ������ OnRecvPacket�� ���ؼ��� Recv�� �Ͽ��� �Ѵ�.
	virtual __int32				OnRecv(unsigned char* bufferPtr, __int32 len) sealed;
	virtual void				OnRecvPacket(unsigned char* bufferPtr, __int32 len) abstract;
};

