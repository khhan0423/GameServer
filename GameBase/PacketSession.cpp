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
		//��Ŷ �ش����� ���� �����͸� �о�����
		//���� �ش� ������ WSARecv�� �Ϸ�Ǿ� OnRecv �� �ٽ� ȣ��Ǳ⸦ ��ٸ���.
		__int32 _dataSize = len - _processLen;
		if (_dataSize < sizeof(PacketHeader))
			break;

		PacketHeader _header = *(reinterpret_cast<PacketHeader*>(&buffer[_processLen]));

		//��Ŷ ��ü ������� ���� �����͸� �о�����
		//���� �ش� ������ WSARecv�� �Ϸ�Ǿ� OnRecv �� �ٽ� ȣ��Ǳ⸦ ��ٸ���.
		if (_dataSize < _header.m_size)
			break;

		//���Ź��ۿ��� ��Ŷ��ŭ �����͸� ���ڷ� �Ѱ��ش�.
		OnRecvPacket(&buffer[_processLen], _header.m_size);

		_processLen += _header.m_size;
	}

	return _processLen;
}
