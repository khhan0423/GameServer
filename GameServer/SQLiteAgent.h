#pragma once
#include "DataBaseBase.h"
#include "SQLiteConnet.h"
#include "SQLiteQuery.h"
#include "FPS.h"

using namespace DataBase;
using namespace DataBase::SQLite3;

class SQLiteDBAgent : public DBAgentInterface<SQLiteQueryBase, SQLiteConnector>
{
	//Agnet�� �������� DB Ŀ�ؼ��� �����Ͽ�����.
	//Agent �� ������ ť�� Regist �ϰ�
	//������ ó�� �Լ��� ����
	//�װ����� ������ ������ ó���ϰ� ��������.

public:
	SQLiteDBAgent();
	~SQLiteDBAgent();

	//�������̽� ����
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
		//������Ʈ���� ���� �����忡�� ���ư��� �κ�
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

			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}		
	}

private:
	std::atomic<bool>			m_isReady = false;
	FPS							m_fps;
	std::thread					m_thread;
};

