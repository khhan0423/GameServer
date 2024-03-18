#pragma once
enum ProtocolResult : __int32
{
	Protocol_Success,
	Protocol_MinorError,					//무시해도 되는 에러
	Protocol_SystemError,					//시스템 에러
	Protocol_PacketError,					//패킷 에러
	Protocol_DataError,						//리소스 데이터 에러
	Protocol_DBError,						//DB 에러
};


