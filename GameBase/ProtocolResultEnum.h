#pragma once
enum ProtocolResult : __int32
{
	Protocol_Success,
	Protocol_MinorError,					//�����ص� �Ǵ� ����
	Protocol_SystemError,					//�ý��� ����
	Protocol_PacketError,					//��Ŷ ����
	Protocol_DataError,						//���ҽ� ������ ����
	Protocol_DBError,						//DB ����
};


