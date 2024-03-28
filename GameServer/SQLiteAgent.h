#pragma once
#include "DataBaseBase.h"
#include "SQLiteConnet.h"
#include "SQLiteQuery.h"
#include "FPS.h"

using namespace DataBase;
using namespace DataBase::SQLite3;

class SQLiteDBAgent : public DBAgentInterface<SQLiteQueryBase, SQLiteConnector>
{
	//Agnet는 독립적인 DB 커넥션을 유지하여야함.
	//Agent 는 쿼리를 큐에 Regist 하고
	//쓰레드 처리 함수를 만들어서
	//그곳에서 쿼리를 실제로 처리하게 만들어야함.

public:
	SQLiteDBAgent();
	~SQLiteDBAgent();

	//인터페이스 구현
	void						Update() override;
	__int32						GetFPS() const override;

public:
	
	bool						Init(const std::string DBName);	
	sqlite3*					GetDBHandler();
	void						SetReady();
	bool						IsRead();

private:
	static void ThreadFunc(void* ptr)
	{
		//에이전트마다 각자 쓰레드에서 돌아가는 부분
		SQLiteDBAgent* pThis = reinterpret_cast<SQLiteDBAgent*>(ptr);		

		while (true)
		{
			if (pThis->m_isReady == false)
				continue;

			if (pThis->m_QueueWait.IsEmpty() == true)
				continue;

			SQLiteQueryBase* pQuery = pThis->m_QueueWait.Pop();
			if (pQuery == nullptr)
				continue;

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

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}		
	}

private:
	std::atomic<bool>			m_isReady = false;
	FPS							m_fps;
	std::thread					m_thread;
};

