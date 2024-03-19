#include "pch.h"
#include "ADO.h"
#include "ADOQuery.h"
#include "ADOAgnet.h"


ADOAgent::ADOAgent(const bool isRun)
{
	if (true == isRun)
		m_hThread = (HANDLE)::_beginthread(ThreadFunc, 0, (void*)this);
}

ADOAgent::~ADOAgent()
{
	if (m_isRun == true)
	{
		m_isRun.exchange(false);
		WaitForSingleObject(m_hThread, INFINITE);
	}

	SAFE_DELETE(m_accountDBPtr);
	SAFE_DELETE(m_gameDBPtr);

	return;
}

void ADOAgent::ThreadFunc(void* pv)
{
	ADOAgent* pThis = (ADOAgent*)pv;
	
	pThis->m_isRun.exchange(true);

	while (pThis->m_isRun)
	{
		pThis->m_fps.Update();

		while (true)
		{
			ADOQuery* pQuery = pThis->m_queueWait.Pop();
			if (pQuery == nullptr)
				break;

			pQuery->Excute(pThis);

			if (pQuery->IsThreadSafeQuery() == false)
			{
				pThis->m_queueComplete.Push(pQuery);
			}
			else
			{
				pQuery->Complete();
				SAFE_DELETE(pQuery);
			}
		}

		Sleep(1);
	}

	return;
}

bool ADOAgent::Init(const string& accountDB, const string& gameDB)
{
	try
	{
		if (m_accountDBPtr == nullptr)
			m_accountDBPtr = new ADO();

		if (m_gameDBPtr == nullptr)
			m_gameDBPtr = new ADO();

		ErrorLog("[%s] - Try connnect to DB - %s", __FUNCTION__, accountDB.c_str());
		if (!m_accountDBPtr->Open(accountDB.c_str()))
		{
			ErrorLog("[%s] GameDB connect failed.", __FUNCTION__);
			return false;
		}

		ErrorLog("[%s] - Try connnect to DB - %s", __FUNCTION__, gameDB.c_str());
		if (!m_gameDBPtr->Open(gameDB.c_str()))
		{
			ErrorLog("[%s] GameDB connect failed.", __FUNCTION__);
			return false;
		}

		return true;
	}
	catch (std::exception& ex)
	{
		ErrorLog("[%s] Exception - %s", __FUNCTION__, ex.what());
		return false;
	}
}

bool ADOAgent::Init(const string& gameDB)
{
	try
	{
		if (m_gameDBPtr == nullptr)
			m_gameDBPtr = new ADO();

		ErrorLog("[%s] - Try connnect to DB - %s", __FUNCTION__, gameDB.c_str());
		if (!m_gameDBPtr->Open(gameDB.c_str()))
		{
			ErrorLog("[%s] GameDB connect failed.", __FUNCTION__);
			return false;
		}

		return true;
	}
	catch (std::exception& ex)
	{
		ErrorLog("[%s] Exception - %s", __FUNCTION__, ex.what());
		return false;
	}
}

void ADOAgent::Update()
{
	while (true)
	{
		ADOQuery* q = m_queueComplete.Pop();
		if (!q) break;

		//long long checktime = timeGetTime();

		q->Complete();

		SAFE_DELETE(q);

		//GetServer()->AddDBCompleteCount(1);
		//GetServer()->AddDBCompleteTime((int)(timeGetTime() - checktime));
	}
}

bool ADOAgent::SyncQuery(ADOQuery* pQuery)
{
	if (pQuery == nullptr)
		return false;

	pQuery->Excute(this);
	pQuery->Complete();

	bool bRet = (pQuery->GetResult() == Protocol_Success);

	SAFE_DELETE(pQuery);

	return bRet;
}