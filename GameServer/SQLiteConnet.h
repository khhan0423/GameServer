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
		//SLQLite DB������ ���� ��ü
		class SQLiteConnector
		{
		public:
			SQLiteConnector();
			virtual ~SQLiteConnector();

		public:
			bool					InitDBName(const std::string& DBfileName);
			sqlite3*				GetHandle();
			bool					IsOpen();
			bool					Open();
			bool					TryOpen();
			void					Close();

		private:
			sqlite3*				m_DBHandlerPtr = nullptr;

		private:
			std::string				m_DBFileName = "";
			std::atomic<bool>		m_isOpen = false;			
		};
	};
}
