#include "pch.h"
#include "SQLiteAgent.h"


SQLiteDBAgent::~SQLiteDBAgent()
{
	if (m_thread.joinable())
		m_thread.join();
}

void SQLiteDBAgent::Update()
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

__int32 SQLiteDBAgent::GetFPS() const
{ 
	return m_fps.GetFPS(); 
}

bool SQLiteDBAgent::Init(const string DBName)
{
	//SQLite 는 파일 이름이 DB 이름이다.
	if (m_DataBase.GetHandle() == nullptr)
	{
		m_DataBase.InitDBName(DBName);
		return (m_DataBase.Open());
	}

	m_thread = thread(ThreadFunc, reinterpret_cast<void*>(this));

	return true;
}

sqlite3* SQLiteDBAgent::GetDBHandler()
{
	//쿼리를 실행하기 위해서 DB 핸들이 필요하다.
	return m_DataBase.GetHandle();
}

void SQLiteDBAgent::SetReady()
{
	m_isReady.exchange(true);
}

bool SQLiteDBAgent::IsRead()
{
	return m_isReady;
}