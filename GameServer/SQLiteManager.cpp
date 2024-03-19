#include "pch.h"
#include "SQLiteManager.h"
#include "SQLiteAgent.h"

bool SQLiteManager::Start()
{
	Stop();

#pragma TODO("컨피그로 DB 쓰레드 몇개돌릴지 세팅하도록 추가해야함.")
	for (int i = 0; i < 2; i++)
	{
		SQLiteDBAgent* pDBAgent = new SQLiteDBAgent;
		if (!pDBAgent->Init("myaccountDB"))
		{
			Stop();
			return false;
		}
		m_DBAgentList.push_back(pDBAgent);
	}

	SystemLog("DB Connect Success");
	
	return true;
}

void SQLiteManager::Stop()
{
	for (auto&& it : m_DBAgentList)
	{
		SAFE_DELETE(it);
	}

	m_DBAgentList.clear();
}

void SQLiteManager::Update()
{
	for (auto&& it : m_DBAgentList)
	{
		it->Update();
	}
}

__int32 SQLiteManager::GetFPS(__int32 index) const
{
	VERIFY_RETURN_VALUE(static_cast<__int32>(index) < m_DBAgentList.size(), -1);
	return m_DBAgentList[index]->GetFPS();
}

__int32 SQLiteManager::GetBadFPS() const
{
	int _badFPS = INT_MAX;
	for (auto&& it : m_DBAgentList)
	{
		if (_badFPS > it->GetFPS())
			_badFPS = it->GetFPS();
	}		
	return _badFPS;
}

void SQLiteManager::SetReady()
{
	for (auto&& _agent : m_DBAgentList)
	{
		_agent->SetReady();
	}
}
