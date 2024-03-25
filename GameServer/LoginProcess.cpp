#include "pch.h"
#include "StringUtil.h"
#include "LoginProcess.h"
#include "SQLiteManager.h"
#include "PacketSession.h"
#include "ClientPacketHandler.h"
#include "Protocol/ProtocolServerToClientEnum.pb.h"
#include "Protocol/ProtocolServerToClient.pb.h"

FindAccount::FindAccount(shared_ptr<PacketSession> sessionShared, const wstring& accountID)
{
	SetSession(sessionShared);	

	m_sql = "SELECT Id, Name FROM Cars;";
	SetDBHandle(GetDBManager()->GetDBAgent(0)->GetDBHandler());	
	AddParam(StringUtil::ToAnsi(accountID));

}

void FindAccount::Complete()
{
	if (IsValid() != SQLITE_OK)
	{
		ErrorLog("[%s] FindAccount Query Invalid", __FUNCTION__);
		return;
	}

	__int32 _resultCount = static_cast<__int32>(m_Result.size());

	shared_ptr<PacketSession> _sessionShared = GetSession();
	if (_sessionShared)
	{
		ProtocolServerToClient::ResultLogin _resultLogin;
		_resultLogin.set_m_playercount(_resultCount);
		_resultLogin.set_m_success(true);
		auto _sendBuffer = ClientPacketHandler::MakeSendBuffer(_resultLogin);
		_sessionShared->Send(_sendBuffer);
	}
}
