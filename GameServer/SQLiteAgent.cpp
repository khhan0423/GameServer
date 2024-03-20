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
		//DBManater ���� Main Thread ���� ������Ʈ���� ��ȸ�ϸ� ȣ��Ǵ� �κ�
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
	//SQLite �� ���� �̸��� DB �̸��̴�.
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
	//������ �����ϱ� ���ؼ� DB �ڵ��� �ʿ��ϴ�.
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