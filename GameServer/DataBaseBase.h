#pragma once
namespace DataBase
{
#define MAX_DEFAULT_DB_CONNECT 1
#define MAX_BUSY_WAIT_TIME 1
#define MAX_BUSY_WAIT_COUNT 60

#define ISFIRSTOCTDIGIT(CH) ((CH) >= '0' && (CH) <= '3')
#define ISOCTDIGIT(CH) ((CH) >= '0' && (CH) <= '7')
#define OCTVAL(CH) ((CH) - '0')

	class DB_Module_Interface
	{
	public:
		DB_Module_Interface() {};
		virtual ~DB_Module_Interface() {};

	public:
		virtual bool Connect(const char* strConnect) abstract;
		virtual void Close() abstract;
		virtual bool IsOpen() abstract;
		virtual bool ReOpen() abstract;

		virtual bool Query(const char* strQuery) abstract;

		virtual bool Fetch() abstract;
		virtual void AllocHandle() abstract;
		virtual void FreeHandle() abstract;

		virtual bool GetData(__int32 nFieldNum, unsigned char* result) abstract;
		virtual bool GetData(__int32 nFieldNum, char* result) abstract;
		virtual bool GetData(__int32 nFieldNum, short* result) abstract;
		virtual bool GetData(__int32 nFieldNum, unsigned short* result) abstract;
		virtual bool GetData(__int32 nFieldNum, __int32* result) abstract;
		virtual bool GetData(__int32 nFieldNum, unsigned __int32* result) abstract;
		virtual bool GetData(__int32 nFieldNum, long long* result) abstract;
		virtual bool GetData(__int32 nFieldNum, unsigned long long* result) abstract;
		virtual bool GetData(__int32 nFieldNum, char* const result, unsigned __int32 nSize) abstract;
		virtual bool GetData(__int32 nFieldNum, double* result) abstract;

		virtual void DisplayErrorMsg() abstract;

	protected:
		__int32 BinaryToText(const unsigned char* pbin, const unsigned long long bin_len, unsigned char* ptext, const unsigned long long text_len);
		__int32 TextToBinary(const unsigned char* ptext, const unsigned long long text_len, unsigned char* pbin, const unsigned long long bin_len);

	protected:
		string		m_strConnect;
	};

	template<class QueryBase, class DataBase_Module>
	class CDBAgentInterface
	{
	public:
		CDBAgentInterface() {};
		virtual ~CDBAgentInterface()
		{
			while (m_QueueWait.Pop()) {}
			while (m_QueueComplete.Pop()) {}
		};

	protected:
		class CQueryQueue
		{
		public:
			virtual ~CQueryQueue()
			{
				{
					lock_guard _lock(m_lock);
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
					lock_guard _lock(m_lock);
					return m_queue.size();
				}
				
			}
			bool IsEmpty() const
			{
				
				{
					lock_guard _lock(m_lock);
					return m_queue.empty();
				}
				
			}
			void Push(QueryBase* q)
			{
				{
					lock_guard _lock(m_lock);
					m_queue.push(q);
				}		
			}
			QueryBase* Pop()
			{
				{
					lock_guard _lock(m_lock);
					QueryBase* q = NULL;
					if (!m_queue.empty())
					{
						q = m_queue.front();
						m_queue.pop();
					}
					return q;
				}
			}

		private:
			mutex				m_lock;
			queue<QueryBase*>	m_queue;
		};

	public:
		virtual void Update() abstract;
		virtual __int32 GetFPS() const abstract;

	public:
		size_t GetWaitQueueCount() const { return m_QueueWait.GetCount(); }
		size_t GetCompleteQueueCount() const { return m_QueueComplete.GetCount(); }

	public:
		void PushQuery(QueryBase* q) { m_QueueWait.Push(q); }

	public:
		virtual bool SyncQuery(QueryBase* /*Query*/) { return true; };

	protected:
		CQueryQueue		m_QueueWait;
		CQueryQueue		m_QueueComplete;

		DataBase_Module	m_DataBase;
	};

	template<class QueryBase, class DataBase_Module>
	class CDBManagerInterface
	{
	public:
		CDBManagerInterface() {};
		virtual ~CDBManagerInterface()
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
		void Insert(__int32 DBGUID, QueryBase* Query)
		{
			if (m_DBAgentList.empty())
				return;

			m_DBAgentList[DBGUID]->PushQuery(Query);

			return;
		}

		CDBAgentInterface<QueryBase, DataBase_Module>* GetDBAgent(__int32 DBGUID)
		{
			if (m_DBAgentList.empty())
				return NULL;

			return m_DBAgentList[DBGUID];
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
		vector<CDBAgentInterface<QueryBase, DataBase_Module>*> m_DBAgentList;
	};
};

