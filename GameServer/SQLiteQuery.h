#pragma once

#include <string>
#include <deque>
#include <sqlite3.h>
#include "DataBaseBase.h"
#include "LogBase.h"
#include "StringUtil.h"

class SQLiteDBAgent;
class PacketSession;
namespace DataBase
{
	namespace SQLite3
	{
		//SQLite Äõ¸®°´Ã¼
		class SQLiteQueryBase
		{
		public:
			~SQLiteQueryBase();
			enum SQPLITE_TYPE
			{
				eINTEGER = 1,
				eINTEGERLONG,
				eDOUBLE,
				eTEXT,
				e_NULL
			};
		public:
			void									AddParamNULL();
			void									AddParam(const bool input);
			void									AddParam(const __int8 input);
			void									AddParam(const __int16 input);
			void									AddParam(const __int32 input);
			void									AddParam(const __int64 input);
			void									AddParam(const float input);
			void									AddParam(const double input);
			void									AddParam(const char* input);
			void									AddParam(const std::string input);
		public:
			void									Prepare();
			void									Bind();
			void									RegistSQLiteParam(const SQPLITE_TYPE type, const std::string str, const int cnt);

			void									Excute(SQLiteDBAgent* agent);
			int										Fetch();
			void									GetValue(const __int32 pos, OUT std::vector<std::string>& outCul);

			void									SetDBHandle(sqlite3* dbHandle);
			__int32									IsValid();
			__int32									GetResultCount();
			void									SetSycnFlag();
			bool									IsSyncQuery();

			virtual void							Complete() abstract {}

		public:
			void									SetSession(std::shared_ptr<PacketSession> sessionShared);
			std::shared_ptr<PacketSession>			GetSession() { return m_SessionShared.lock(); }

		public:
			std::string								m_sql;
			std::vector<std::vector<std::string>>	m_Result;
		private:
			std::atomic<bool>						m_isSyncQuery = false;
			__int32									m_excuteResult = SQLITE_OK;
			__int32									m_commandResult = SQLITE_ERROR;
			std::vector<std::pair<SQPLITE_TYPE,		std::string>>	m_Params;			
			sqlite3_stmt*							m_res = nullptr;
			sqlite3*								m_db = nullptr;

		private:
			std::weak_ptr<PacketSession>			m_SessionShared;
		};
	}
}