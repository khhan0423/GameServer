#pragma once
#include <string>
#include <deque>
#include <sqlite3.h>
#include "DataBaseBase.h"
#include "LogBase.h"
#include "StringUtil.h"


int busy_handler(void* pArg, int nCallCount);

struct sqlite3;
struct sqlite3_stmt;

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
			bool Init(const string& DBfileName)
			{
				m_DBFileName = DBfileName;
				return true;
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

		//SQLite 쿼리객체
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
			void AddParamNULL()
			{
				m_Params.push_back(make_pair(e_NULL, "0"));
			}
			void AddParam(const bool input)
			{
				m_Params.push_back(make_pair(eINTEGER, StringUtil::IntToAnsi(input)));
			}
			void AddParam(const __int8 input)
			{
				m_Params.push_back(make_pair(eINTEGER, StringUtil::IntToAnsi(input)));
			}
			void AddParam(const __int16 input)
			{
				m_Params.push_back(make_pair(eINTEGER, StringUtil::IntToAnsi(input)));
			}
			void AddParam(const __int32 input)
			{
				m_Params.push_back(make_pair(eINTEGER, StringUtil::IntToAnsi(input)));
			}
			void AddParam(const __int64 input)
			{
				m_Params.push_back(make_pair(eINTEGERLONG, StringUtil::IntToAnsi(input)));
			}
			void AddParam(const float input)
			{
				m_Params.push_back(make_pair(eDOUBLE, StringUtil::FloatToAnsi(input)));
			}
			void AddParam(const double input)
			{
				m_Params.push_back(make_pair(eDOUBLE, StringUtil::DoubleToAnsi(input)));
			}
			void AddParam(const char* input)
			{
				m_Params.push_back(make_pair(eTEXT, input));
			}
			void AddParam(const string input)
			{
				m_Params.push_back(make_pair(eTEXT, input));
			}
		public:
			bool Prepare()
			{
				int ret = sqlite3_prepare_v2(m_db, m_sql.c_str(), -1, &m_res, 0);
				if (ret != SQLITE_OK)
				{
					ErrorLog("[%s] - Failed Prepare return Val : %d", __FUNCTION__, ret);
					return false;
				}
				return true;
			}
			void Bind()
			{
				for (int i = 0; i < m_Params.size(); i++)
				{
					RegistSQLiteParam(m_Params[i].first, m_Params[i].second, i + 1);
				}
			}
			void RegistSQLiteParam(const SQPLITE_TYPE type, const string str, const int cnt)
			{
				switch (type)
				{
				case eINTEGER: sqlite3_bind_int(m_res, cnt, stoi(str));
					return;
				case eINTEGERLONG:sqlite3_bind_int64(m_res, cnt, stoll(str));
					return;
				case eDOUBLE:sqlite3_bind_double(m_res, cnt, stod(str));
					return;
				case eTEXT:
				{
					//무조건 UTF-8로 변환해서 DB에 저장 SQLITE3 DB의 기본 인코딩이 UTF-8
					string _utf8Str = StringUtil::AnsiToUtf8(str);
					sqlite3_bind_text(m_res, cnt, _utf8Str.c_str(), static_cast<__int32>(_utf8Str.length()), SQLITE_TRANSIENT);
					return;
				}
				case e_NULL: sqlite3_bind_null(m_res, cnt);
					return;
				default:
					return;
				}
			}

			void Excute()
			{
				Prepare();

				Bind();

				m_commandResult = Fetch();

				if (m_commandResult != SQLITE_DONE)
				{
					ErrorLog("[%s] - Failed Excute retrn Val : %d", __FUNCTION__, m_commandResult);
				}
				return;

				Complete();
			}

			int Fetch()
			{
				int step = sqlite3_step(m_res);

				vector<string> outCul;
				while (step == SQLITE_ROW)
				{
					const int _columnCnt = sqlite3_data_count(m_res);
					for (int i = 0; i < _columnCnt; i++)
					{
						GetValue(i, outCul);
					}
					m_Result.push_back(outCul);
					step = sqlite3_step(m_res);
				}

				sqlite3_finalize(m_res);

				return step;
			}

			void GetValue(const __int32 pos, OUT vector<string>& outCul)
			{
				//무조껀 String 으로 받아서 outCul에 저장
				//꺼내쓰는 쪽이 변환해서 사용
				const char* _strPtr = reinterpret_cast<const char*>(sqlite3_column_text(m_res, pos));
				const string _outStr = _strPtr;
				outCul.push_back(_outStr);
			}

			virtual void Complete()
			{
				//상속받은 애가 오버라이드
			}

			void SetDBHandle(sqlite3* dbHandle)
			{
				m_db = dbHandle;
			}

			__int32 GetCommandResult()
			{
				return m_commandResult;
			}
		public:
			string								m_sql;
		private:
			__int32								m_commandResult = SQLITE_ERROR;
			vector<pair<SQPLITE_TYPE, string>>	m_Params;
			vector<vector<string>>				m_Result;
			sqlite3_stmt* m_res;
			sqlite3* m_db;
		};
	};
}
