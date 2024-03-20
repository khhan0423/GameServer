#pragma once
#include "DataBaseBase.h"
#include "SQLiteConnet.h"
#include "SQLiteQuery.h"
#include "FPS.h"

using namespace DataBase;
using namespace DataBase::SQLite3;

//쿼리

class SQLiteDBAgent : public DBAgentInterface<SQLiteQueryBase, SQLiteConnector>
{
	//Agnet는 독립적인 DB 커넥션을 유지하여야함.
	//Agent 는 쿼리를 큐에 Regist 하고
	//쓰레드 처리 함수를 만들어서
	//그곳에서 쿼리를 실제로 처리하게 만들어야함.

public:
	SQLiteDBAgent()
	{
		
	}
	~SQLiteDBAgent()
	{
		if(m_thread.joinable())
			m_thread.join();
	}

	//인터페이스 구현
	void Update() override
	{
		while (true)
		{
			//DBManater 에서 Main Thread 에서 에이전트별로 순회하며 호출되는 부분
			SQLiteQueryBase* _query = m_QueueComplete.Pop();
			if (_query == nullptr)
				break;

			_query->Complete();

			SAFE_DELETE(_query);
		}		

	}
	__int32 GetFPS() const override { return m_fps.GetFPS(); }

public:
	//SQLite 는 파일 이름이 DB 이름이다.
	bool Init(const string DBName)
	{
		if (m_DataBase.GetHandle() == nullptr)
		{
			m_DataBase.InitDBName(DBName);
			return (m_DataBase.Open());
		}

		m_thread = thread(ThreadFunc, reinterpret_cast<void*>(this));

		return true;
	}

	//쿼리를 실행하기 위해서 DB 핸들이 필요하다.
	sqlite3* GetDBHandler()
	{
		return m_DataBase.GetHandle();
	}

	void SetReady()
	{
		m_isReady.exchange(true);
	}

	bool IsRead()
	{
		return m_isReady;
	}

private:
	static void ThreadFunc(void* pv)
	{
		//에이전트마다 각자 쓰레드에서 돌아가는 부분
		SQLiteDBAgent* pThis = reinterpret_cast<SQLiteDBAgent*>(pv);		

		while (true)
		{
			if (pThis->m_isReady == false)
				break;

			SQLiteQueryBase* pQuery = pThis->m_QueueWait.Pop();
			if (pQuery == nullptr)
				break;

			pQuery->Excute(pThis);

			if (pQuery->IsSyncQuery() == false)
			{
				//쿼리 완료큐로 옮긴다음
				//complete 호출을 기다린다.
				pThis->m_QueueComplete.Push(pQuery);
			}
			else
			{
				//쿼리 실행 즉시 후처리를 하여야 하는 경우가 있다.
				pQuery->Complete();
				SAFE_DELETE(pQuery);
			}

			this_thread::sleep_for(chrono::milliseconds(1));
		}		
	}


private:
	atomic<bool>			m_isReady = false;
	FPS						m_fps;
	thread					m_thread;
};

