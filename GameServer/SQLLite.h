#pragma once
#include "DataBaseBase.h"

__int32 busy_handler(void* pArg, __int32 nCallCount);

struct sqlite3;
struct sqlite3_stmt;

namespace DataBase
{
	namespace SQLite3
	{
		class CSQLite : CDB_Module_Interface
		{
		public:
			CSQLite();
			virtual ~CSQLite();

		public:
			bool Init();
			void SetFlag(__int32 flag) { m_flag = flag; }
			__int32 GetFlag() { return m_flag; }

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

			virtual bool GetData(__int32 nFieldNum, unsigned char* result)  override;
			virtual bool GetData(__int32 nFieldNum, char* result)  override;
			virtual bool GetData(__int32 nFieldNum, short* result) override;
			virtual bool GetData(__int32 nFieldNum, unsigned short* result) override;
			virtual bool GetData(__int32 nFieldNum, __int32* result) override;
			virtual bool GetData(__int32 nFieldNum, unsigned int* result) override;
			virtual bool GetData(__int32 nFieldNum, long long* result) override;
			virtual bool GetData(__int32 nFieldNum, unsigned long long* result) override;
			virtual bool GetData(__int32 nFieldNum, char* const result, unsigned __int32 len) override;
			virtual bool GetData(__int32 nFieldNum, double* result) override;

			virtual void DisplayErrorMsg() override;

		public:
			int GetDataBytea(__int32 nFieldNum, unsigned char* const result, unsigned __int32 len);
			int SetDataBytea(const unsigned char* bintext, size_t binlen, unsigned char* rettext, size_t retlen);

		private:
			sqlite3* m_pDB;
			sqlite3_stmt* m_stmt;

		private:
			bool			m_handleOpenCheck;
			__int32			m_flag;
		};
	};
};

