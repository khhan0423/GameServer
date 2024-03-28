#pragma once
#include "LogBase.h"
namespace DataBase
{
#define MAX_BUSY_WAIT_TIME 20
#define MAX_BUSY_WAIT_COUNT 60

	template<class QueryBase, class DataBase_ConnectModule>	
	class DBAgentInterface
	{
	public:
		DBAgentInterface() {};
		virtual ~DBAgentInterface()
		{
			while (m_QueueWait.Pop()) {}
			while (m_QueueComplete.Pop()) {}
		};

	protected:
		class QueryQueue
		{
		public:
			virtual ~QueryQueue()
			{
				{
					std::lock_guard<std::mutex> _lock(m_lock);
					while (!m_queue.empty())
					{
						QueryBase* q = m_queue.front();
						m_queue.pop();
						SAFE_DELETE(q);
					}
				}
			}
		public:
			size_t GetCount() const
			{
				{
					std::lock_guard<std::mutex> _lock(m_lock);
					return m_queue.size();
				}
				
			}
			bool IsEmpty() const
			{
				
				{
					std::lock_guard<std::mutex> _lock(m_lock);
					return m_queue.empty();
				}
				
			}
			void Push(QueryBase* q)
			{
				{
					std::lock_guard<std::mutex> _lock(m_lock);
					m_queue.push(q);
				}		
			}
			QueryBase* Pop()
			{
				{
					std::lock_guard<std::mutex> _lock(m_lock);
					QueryBase* q = nullptr;
					if (!m_queue.empty())
					{
						q = m_queue.front();
						m_queue.pop();
					}
					return q;
				}
			}

		private:
			mutable std::mutex		m_lock;
			std::queue<QueryBase*>	m_queue;
		};

	public:
		virtual void Update() abstract;
		virtual __int32 GetFPS() const abstract;

	public:
		size_t GetWaitQueueCount() const { return m_QueueWait.GetCount(); }
		size_t GetCompleteQueueCount() const { return m_QueueComplete.GetCount(); }

	public:
		void PushQuery(QueryBase* q) { m_QueueWait.Push(q); }

	protected:
		QueryQueue				m_QueueWait;
		QueryQueue				m_QueueComplete;

		DataBase_ConnectModule	m_DataBase;
	};

	template<class QueryBase, class DBAgnet>
	class DBManagerInterface
	{
	public:
		DBManagerInterface() {};
		virtual ~DBManagerInterface()
		{
			for (auto&& it : m_DBAgentList)
				SAFE_DELETE(it);

			m_DBAgentList.clear();

			return;
		};

	public:
		virtual bool Start() abstract;
		virtual void Stop() abstract;
		virtual void Update() abstract;

	public:
		virtual __int32 GetFPS(__int32 index) const abstract;
		virtual __int32 GetBadFPS() const = 0;

	public:
		void Insert(__int32 globalUniqueID, QueryBase* Query)
		{
			if (m_DBAgentList.empty())
				return;
			//같은 유니크 ID 를 가진 객체는 같은 DB 커넥션에서 같은 쿼리큐를 사용하도록
			m_DBAgentList[globalUniqueID % m_DBAgentList.size()]->PushQuery(Query);

			return;
		}

		DBAgnet* GetDBAgent(__int32 globalUniqueID)
		{
			if (m_DBAgentList.empty())
				return NULL;
			//같은 유니크 ID 를 가진 객체는 같은 DB 커넥션에서 같은 쿼리큐를 사용하도록
			return m_DBAgentList[globalUniqueID % m_DBAgentList.size()];
		}

		unsigned long long GetAgentCount() const
		{
			return m_DBAgentList.size();
		}
		int GetWaitQueueCount(__int32 index) const
		{
			VERIFY_RETURN_VALUE(static_cast<unsigned long long>(index) < m_DBAgentList.size(), -1);
			return static_cast<__int32>(m_DBAgentList[index]->GetWaitQueueCount());
		}

		int GetCompleteQueueCount(__int32 index) const
		{
			VERIFY_RETURN_VALUE(static_cast<unsigned long long>(index) < m_DBAgentList.size(), -1);
			return static_cast<__int32>(m_DBAgentList[index]->GetCompleteQueueCount());
		}

	protected:
		std::vector<DBAgnet*> m_DBAgentList;
	};
};

