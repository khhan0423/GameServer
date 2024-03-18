#pragma once
#include "DataBaseBase.h"

int busy_handler(void* pArg, int nCallCount);

struct sqlite3;
struct sqlite3_stmt;

namespace DataBase
{
	namespace SQLite3
	{
		class SQLite : DB_Module_Interface
		{
		public:
			SQLite();
			virtual ~SQLite();

		public:
			bool Init();
			void SetFlag(int nFlag) { m_nFlag = nFlag; }
			int GetFlag() { return m_nFlag; }

			bool IsEmptyConnString() { return m_strConnect.empty(); }
			const char* GetConnString() { return m_strConnect.c_str(); }
			void SetConnString(const char* connString) { m_strConnect.clear(); m_strConnect = connString; }

		public: //Virtual
			virtual bool Connect(const char* strConnect) override;
			virtual void Close() override;
			virtual bool IsOpen() override;
			virtual bool ReOpen() override;

			virtual bool Query(const char* strQuery) override;
			bool QueryExec(const char* strQuery);

			virtual bool Fetch() override;
			virtual void AllocHandle() override;
			virtual void FreeHandle() override;

			virtual bool GetData(int nFieldNum, unsigned char* result)  override;
			virtual bool GetData(int nFieldNum, char* result)  override;
			virtual bool GetData(int nFieldNum, short* result) override;
			virtual bool GetData(int nFieldNum, unsigned short* result) override;
			virtual bool GetData(int nFieldNum, int* result) override;
			virtual bool GetData(int nFieldNum, unsigned int* result) override;
			virtual bool GetData(int nFieldNum, long long* result) override;
			virtual bool GetData(int nFieldNum, unsigned long long* result) override;
			virtual bool GetData(int nFieldNum, char* const result, unsigned int nSize) override;
			virtual bool GetData(int nFieldNum, double* result) override;

			virtual void DisplayErrorMsg() override;

		public:
			int GetDataBytea(int nFieldNum, unsigned char* const result, unsigned int nSize);
			int SetDataBytea(const unsigned char* bintext, size_t binlen, unsigned char* rettext, size_t retlen);

		private:
			sqlite3* m_pDB;
			sqlite3_stmt* m_stmt;

		private:
			bool			m_bHandleOpenCheck;
			int				m_nFlag;
		};
	};
}
