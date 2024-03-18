#include "pch.h"
#include <vector>
#include "ADOManager.h"
#include "ADOAgnet.h"


bool ADOManager::Start()
{
	Stop();
#pragma TODO("나중에 컨피그 에서 읽어와서 DB ADO 문자열 가져와서 세팅하도록 바꾸어야 한다.")
	m_pDBAgentForPool = new ADOAgent(false);

	//DBConnectString 을 인자 값으로 넘겨주어야 한다.
	//DBConnectString 형식
	//"Provider=SQLOLEDB.1;Data Source=172.0.0.1 ,12345;
	//Initial Catalog=;
	//User id=;
	//Password=;
	//Timeout=30;
	//Min Pool Size=60;
	//Max Pool Size=80;
	//Trusted_connection=true;"

	string _accountDBConnectionStr = "";
	string _GameDBConnectionStr = "";
	if (m_pDBAgentForPool->Init(_accountDBConnectionStr, _GameDBConnectionStr) == false)
	{
		Stop();
		return false;
	}

#pragma TODO("나중에 컨피그 에서 읽어와서 DB 쓰레그 숫자 세팅하도록 바꾸어야 한다.")
	for (int i = 0; i < 2; i++)
	{
		ADOAgent* pDBAgent = new ADOAgent;
		if (m_pDBAgentForPool->Init(_accountDBConnectionStr, _GameDBConnectionStr) == false)
		{
			Stop();
			return false;
		}
		m_DBAgentList.push_back(pDBAgent);
	}

	SystemLog("DB Connect Success");

	return true;
}

void ADOManager::Stop()
{

	for (auto&& it : m_DBAgentList)
		SAFE_DELETE(it);

	m_DBAgentList.clear();

	SAFE_DELETE(m_pDBAgentForPool);
}

void ADOManager::Update()
{
	for (auto&& it : m_DBAgentList)
		it->Update();

	return;
}

void ADOManager::Insert(int DBGUID, ADOQuery* query)
{
	if (m_DBAgentList.empty()) return;
	m_DBAgentList[DBGUID % m_DBAgentList.size()]->PushQuery(query);
}

ADOAgent* ADOManager::GetDBAgent(int DBGUID)
{
	if (m_DBAgentList.empty())
		return NULL;

	return m_DBAgentList[DBGUID % m_DBAgentList.size()];
}

int ADOManager::GetFPS(int index) const
{
	VERIFY_RETURN_VALUE(static_cast<size_t>(index) < m_DBAgentList.size(), -1);
	return m_DBAgentList[index]->GetFPS();
}

int ADOManager::GetBadFPS() const
{
	int _badFPS = INT_MAX;
	for (auto&& it : m_DBAgentList) if (_badFPS > it->GetFPS()) _badFPS = it->GetFPS();
	return _badFPS;
}

int ADOManager::GetWaitQueueCount(int index) const
{
	VERIFY_RETURN_VALUE(static_cast<size_t>(index) < m_DBAgentList.size(), -1);
	return static_cast<int>(m_DBAgentList[index]->GetWaitQueueCount());
}

int ADOManager::GetCompleteQueueCount(int index) const
{
	VERIFY_RETURN_VALUE(static_cast<size_t>(index) < m_DBAgentList.size(), -1);
	return static_cast<int>(m_DBAgentList[index]->GetCompleteQueueCount());
}