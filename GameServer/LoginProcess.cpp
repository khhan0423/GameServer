#include "pch.h"
#include "StringUtil.h"
#include "LoginProcess.h"
#include "SQLiteManager.h"
#include "PacketSession.h"
#include "ClientPacketHandler.h"
#include "Protocol/ProtocolServerToClientEnum.pb.h"
#include "Protocol/ProtocolServerToClient.pb.h"

FindAccount::FindAccount(std::shared_ptr<PacketSession> sessionShared, const std::wstring& accountID)
{
	SetSession(sessionShared);
	SetDBHandle(GetDBManager()->GetDBAgent(sessionShared->GetSessionGUID())->GetDBHandler());

	m_sql = "SELECT account_id FROM GAME_ACCOUNT WHERE account_id = ?;";
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

	std::shared_ptr<PacketSession> _sessionShared = GetSession();
	if (_sessionShared)
	{
		ProtocolServerToClient::ResultLogin _resultLogin;
		_resultLogin.set_m_playercount(_resultCount);
		_resultLogin.set_m_success(true);
		auto _sendBuffer = ClientPacketHandler::MakeSendBuffer(_resultLogin);
		_sessionShared->Send(_sendBuffer);
	}
}

CreateAccount::CreateAccount(std::shared_ptr<PacketSession> sessionShared, const std::wstring& accountID)
{
	SetSession(sessionShared);
	SetDBHandle(GetDBManager()->GetDBAgent(sessionShared->GetSessionGUID())->GetDBHandler());

	m_sql = "INSERT INTO GAME_ACCOUNT (account_id) VALUES (?);";
	AddParam(StringUtil::ToAnsi(accountID));
}

void CreateAccount::Complete()
{
	if (IsValid() != SQLITE_OK)
	{
		ErrorLog("[%s] FindAccount Query Invalid", __FUNCTION__);
		return;
	}

	std::shared_ptr<PacketSession> _sessionShared = GetSession();
	if (_sessionShared)
	{
		ProtocolServerToClient::ResultCreateAccount _resu_CreateAccount;
		_resu_CreateAccount.set_m_success(true);
		auto _sendBuffer = ClientPacketHandler::MakeSendBuffer(_resu_CreateAccount);
		_sessionShared->Send(_sendBuffer);
	}
}
