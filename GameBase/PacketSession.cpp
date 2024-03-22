#include "pch.h"
#include "LogBase.h"
#include "PacketSession.h"

PacketSession::PacketSession()
{
	DebugLog("[%s]", __FUNCTION__);
}

PacketSession::~PacketSession()
{
	DebugLog("[%s]", __FUNCTION__);
}

__int32 PacketSession::OnRecv(unsigned char* buffer, __int32 len)
{
	DebugLog("[%s] len : ", __FUNCTION__, len);
	__int32 _processLen = 0;

	while (true)
	{
		//패킷 해더보다 적은 데이터를 읽었으면
		//다음 해당 세션의 WSARecv가 완료되어 OnRecv 가 다시 호출되기를 기다린다.
		__int32 _dataSize = len - _processLen;
		if (_dataSize < sizeof(PacketHeader))
			break;

		PacketHeader _header = *(reinterpret_cast<PacketHeader*>(&buffer[_processLen]));

		//패킷 전체 사이즈보다 적은 데이터를 읽었으면
		//다음 해당 세션의 WSARecv가 완료되어 OnRecv 가 다시 호출되기를 기다린다.
		if (_dataSize < _header.m_size)
			break;

		//수신버퍼에서 패킷만큼 데이터를 인자로 넘겨준다.
		OnRecvPacket(&buffer[_processLen], _header.m_size);

		_processLen += _header.m_size;
	}

	return _processLen;
}
