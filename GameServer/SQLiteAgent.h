#pragma once
#include "DataBaseBase.h"
#include "SQLiteConnet.h"
#include "SQLiteQuery.h"
#include "FPS.h"

using namespace DataBase;
using namespace DataBase::SQLite3;

//����

class SQLiteDBAgent : public DBAgentInterface<SQLiteQueryBase, SQLiteConnector>
{
	//Agnet�� �������� DB Ŀ�ؼ��� �����Ͽ�����.
	//Agent �� ������ ť�� Regist �ϰ�
	//������ ó�� �Լ��� ����
	//�װ����� ������ ������ ó���ϰ� ��������.

public:
	SQLiteDBAgent()
	{
		
	}
	~SQLiteDBAgent()
	{
		if(m_thread.joinable())
			m_thread.join();
	}

	//�������̽� ����
	void Update() override
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
	__int32 GetFPS() const override { return m_fps.GetFPS(); }

public:
	//SQLite �� ���� �̸��� DB �̸��̴�.
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

	//������ �����ϱ� ���ؼ� DB �ڵ��� �ʿ��ϴ�.
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
		//������Ʈ���� ���� �����忡�� ���ư��� �κ�
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
				//���� �Ϸ�ť�� �ű����
				//complete ȣ���� ��ٸ���.
				pThis->m_QueueComplete.Push(pQuery);
			}
			else
			{
				//���� ���� ��� ��ó���� �Ͽ��� �ϴ� ��찡 �ִ�.
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

