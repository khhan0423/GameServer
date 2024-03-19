#pragma once

#include <string>
#include <deque>
#include <sqlite3.h>
#include "DataBaseBase.h"
#include "LogBase.h"
#include "StringUtil.h"

class SQLiteDBAgent;

namespace DataBase
{
	namespace SQLite3
	{
		//SQLite ������ü
		class SQLiteQueryBase
		{
		public:
			enum SQPLITE_TYPE
			{
				eINTEGER = 1,
				eINTEGERLONG,
				eDOUBLE,
				eTEXT,
				e_NULL
			};
		public:
			void AddParamNULL();
			void AddParam(const bool input);
			void AddParam(const __int8 input);
			void AddParam(const __int16 input);
			void AddParam(const __int32 input);
			void AddParam(const __int64 input);
			void AddParam(const float input);
			void AddParam(const double input);
			void AddParam(const char* input);
			void AddParam(const string input);
		public:
			bool Prepare();
			void Bind();
			void RegistSQLiteParam(const SQPLITE_TYPE type, const string str, const int cnt);

			void Excute(SQLiteDBAgent* agent);
			int Fetch();
			void GetValue(const __int32 pos, OUT vector<string>& outCul);

			void SetDBHandle(sqlite3* dbHandle);
			__int32 GetCommandResult();
			void SetSycnFlag();
			bool IsSyncQuery();
		
		public:
			virtual void Complete() abstract
			{
				//������ Ưȭ�ؼ� ��ӕ��� ����
			}

		public:
			string								m_sql;
		private:
			atomic<bool>						m_isSyncQuery = false;
			__int32								m_commandResult = SQLITE_ERROR;
			vector<pair<SQPLITE_TYPE, string>>	m_Params;
			vector<vector<string>>				m_Result;
			sqlite3_stmt* m_res;
			sqlite3* m_db;
		};
	}
}
//	���� ���� 
//	Select
//	SQLiteQueryBase command;
//	command.m_sql = "SELECT Id, Name FROM cars WHERE Name = ? or Name = ?";
//	command.SetDBHandle(db);	
//	command.AddParam("Audi");
//	command.AddParam("Volvo");
//	command.Excute();
//	int _result = command.GetCommandResult();

//	Insert
//	SQLiteQueryBase command;
//	command.m_sql = "INSERT INTO cars(Id, NAME, Price) VALUES(?, ?, ?)";
//	command.SetDBHandle(db);
//	command.AddParam(10);
//	command.AddParam("HYUNDAI");
//	command.AddParam(31000);
//	command.Excute();
//	int _result = command.GetCommandResult();

//	Delete
//	SQLiteQueryBase command;
//	command.m_sql = "DELETE FROM cars WHERE Id = ?";
//	command.SetDBHandle(db);
//	command.AddParam(3);
//	command.Excute();
//	int _result = command.GetCommandResult();

//	Update
//	SQLiteQueryBase command;
//	command.m_sql = "UPDATE cars SET Price = ? WHERE Name = ?";
//	command.SetDBHandle(db);
//	command.AddParam(20000);
//	command.AddParam("Audi");
//	command.Excute();
//	int _result = command.GetCommandResult();