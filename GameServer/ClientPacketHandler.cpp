#include "pch.h"
#include "LogBase.h"
#include "StringUtil.h"
#include "ClientPacketHandler.h"
#include "SQLiteManager.h"
#include "LoginProcess.h"

PacketHandlerFunc GPacketHandler[UINT16_MAX];

bool Handle_INVALID(std::shared_ptr<PacketSession>& session, unsigned char* buffer, __int32 len)
{
	DebugLog("[%s]", __FUNCTION__);
	PacketHeader* _header = reinterpret_cast<PacketHeader*>(buffer);
	return false;
}

bool Handle_RequestLogin(std::shared_ptr<PacketSession>& session, ProtocolClientToServer::RequestLogin& pkt)
{
	DebugLog("[%s]", __FUNCTION__);	
	std::wstring _accountID = StringUtil::Utf8ToWide(pkt.m_accountid());
	GetDBManager()->Insert(0, new FindAccount(session, _accountID));

	return true;
}

bool Handle_RequestCreateAccount(std::shared_ptr<PacketSession>& session, ProtocolClientToServer::RequestCreateAccount& pkt)
{
	DebugLog("[%s]", __FUNCTION__);
	std::wstring _accountID = StringUtil::Utf8ToWide(pkt.m_accountid());
	GetDBManager()->Insert(0, new CreateAccount(session, _accountID));

	return true;
}
