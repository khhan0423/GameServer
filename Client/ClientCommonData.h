#pragma once
#include "SingletonBase.h"
#include "StringUtil.h"

#define ClientGlobalData() ClientCommonData::GetInstance()

class ClientCommonData : public TSingletonBase<ClientCommonData>
{
public:
	std::wstring				m_AccountID;
	std::vector<std::wstring>	m_CaracterIDS;

	std::atomic<bool>			m_isConnected = false;;

	std::string					GetONOFFLine() { return (m_isConnected == true ? "On Line" : "Off Line"); }
	std::string					GetAccountID() { return (m_AccountID.empty() == true ? " " : StringUtil::WideToUtf8(m_AccountID)); }
};

