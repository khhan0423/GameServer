#pragma once
#include <string>
#include <deque>
#include <sqlite3.h>
#include "DataBaseBase.h"
#include "LogBase.h"
#include "StringUtil.h"

int busy_handler(void* pArg, int nCallCount);
namespace DataBase
{
	namespace SQLite3
	{
		//SLQLite DB연결을 위한 객체
		class SQLiteConnector
		{
		public:
			SQLiteConnector();
			virtual ~SQLiteConnector()
			{
				Close();
			}

		public:
			bool InitDBName(const string& DBfileName)
			{
				m_DBFileName = DBfileName;
				return true;
			}

			sqlite3* GetHandle()
			{
				return m_DBHandlerPtr;
			}

			bool IsOpen()
			{
				return m_isOpen;
			}

			bool Open()
			{
				return TryOpen();
			}

			bool TryOpen();

			void Close();
		private:
			sqlite3* m_DBHandlerPtr = nullptr;

		private:
			string					m_DBFileName = "";
			atomic<bool>			m_isOpen = false;			
		};
	};
}
