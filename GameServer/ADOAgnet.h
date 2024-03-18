#pragma once

#include <mutex>
#include "ADO.h"
#include "ADOQuery.h"

using namespace DataBase;
using namespace DataBase::SQLite3;

class ADOAgent
{
protected:
	class CQueryQueue
	{
	private:
		mutable mutex			m_lock;
		std::queue<ADOQuery*>	m_queue;

	public:
		virtual ~CQueryQueue()
		{
			lock_guard<mutex> _lock(m_lock);
			while (!m_queue.empty())
			{
				ADOQuery* q = m_queue.front();
				m_queue.pop();
				SAFE_DELETE(q);
			}
		}
		size_t GetCount() const
		{
			lock_guard<mutex> _lock(m_lock);
			return m_queue.size();
		}
		bool IsEmpty() const
		{
			lock_guard<mutex> _lock(m_lock);
			return m_queue.empty();
		}
		void Push(ADOQuery* q)
		{
			lock_guard<mutex> _lock(m_lock);
			m_queue.push(q);
		}
		ADOQuery* Pop()
		{
			lock_guard<mutex> _lock(m_lock);
			ADOQuery* q = NULL;
			if (!m_queue.empty())
			{
				q = m_queue.front();
				m_queue.pop();
			}
			return q;
		}
	};

private:
	ADO*					m_accountDBPtr = nullptr;
	ADO*					m_gameDBPtr = nullptr;

	bool					m_bRun;
	HANDLE					m_hThread;
	CQueryQueue				m_queueWait;
	CQueryQueue				m_queueComplete;

	DataBaseCoInitialize	m_coInit;

public:
	ADOAgent(const bool isRun = true);
	virtual ~ADOAgent();

private:
	static void ThreadFunc(void* pv);

public:
	ADO* GetAccountDB() { return m_accountDBPtr; }
	ADO* GetGameDB() { return m_gameDBPtr; }

public:
	bool Init(const string & accountDB);
	void Update();

	size_t GetWaitQueueCount() const { return m_queueWait.GetCount(); }
	size_t GetCompleteQueueCount() const { return m_queueComplete.GetCount(); }

public:
	void PushQuery(ADOQuery * q) { m_queueWait.Push(q); }
};