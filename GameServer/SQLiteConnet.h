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
			virtual ~SQLiteConnector();

		public:
			bool					InitDBName(const string& DBfileName);
			sqlite3*				GetHandle();
			bool					IsOpen();
			bool					Open();
			bool					TryOpen();
			void					Close();

		private:
			sqlite3*				m_DBHandlerPtr = nullptr;

		private:
			string					m_DBFileName = "";
			atomic<bool>			m_isOpen = false;			
		};
	};
}
