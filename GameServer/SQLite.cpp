#include "pch.h"
#include <sqlite3.h>
#include "SQLite.h"
#include "LogBase.h"

using namespace DataBase::SQLite3;

int busy_handler(void* /*pArg*/, int nCallCount)
{
	if (nCallCount < MAX_BUSY_WAIT_COUNT)
	{
		Sleep(MAX_BUSY_WAIT_TIME);
		return 1;
	}
	return 0;
}

SQLite::SQLite() : m_pDB(NULL), m_stmt(NULL), m_bHandleOpenCheck(false), m_nFlag(0)
{
}

SQLite::~SQLite()
{
	if (IsOpen())
		Close();
}

bool SQLite::Init()
{
	int nError = sqlite3_open_v2(GetConnString(), &m_pDB, GetFlag(), NULL);
	if (nError != SQLITE_OK)
	{
		ErrorLog("[%s] - Open Sqlite[%s] is Failed : Code(%d)", __FUNCTION__, GetConnString(), nError);
		return false;
	}

	if (sqlite3_busy_handler(m_pDB, busy_handler, NULL) != SQLITE_OK)
	{
		ErrorLog("Busy Hadler Regist Failed");
		return false;
	}

	std::string PragmaString =
		std::string("PRAGMA temp_store = 2;") +
		std::string("PRAGMA journal_mode = WAL;") +
		std::string("PRAGMA synchronous = OFF;") +
		std::string("PRAGMA locking_mode = EXCLUSIVE;") +
		std::string("PRAGMA encoding = \"UTF-8\";");

	if (sqlite3_exec(m_pDB, PragmaString.c_str(), NULL, NULL, NULL) != SQLITE_OK)
	{
		ErrorLog("Sqlite Exec Error");
		return false;
	}

	if (sqlite3_exec(m_pDB, "vacuum;", NULL, NULL, NULL) != SQLITE_OK)
	{
		ErrorLog("Sqlite Exec Error");
		return false;
	}

	return true;
}

bool SQLite::Connect(const char* strConnect)
{
	if (IsOpen())
		return false;

	SetFlag(SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
	SetConnString(strConnect);

	return Init();
}

bool SQLite::IsOpen()
{
	if (m_pDB != NULL)
		return true;

	DebugLog("[%s] Closed", __FUNCTION__);

	return false;
}

bool SQLite::ReOpen()
{
	Close();

	return Init();
}

void SQLite::Close()
{
	if (!m_pDB) return;

	if (sqlite3_close(m_pDB) != SQLITE_OK)
		DebugLog("[%s] Close Failed", __FUNCTION__);

	m_pDB = NULL;
}

bool SQLite::Query(const char* strQuery)
{
	if (sqlite3_prepare_v2(m_pDB, strQuery, static_cast<int>(strlen(strQuery)), &m_stmt, NULL) != SQLITE_OK)
	{
		ErrorLog("[%s] - Failed Prepare Query[%s]", __FUNCTION__, strQuery);
		return false;
	}

	return true;
}

bool SQLite::QueryExec(const char* strQuery)
{
	if (sqlite3_exec(m_pDB, strQuery, NULL, NULL, NULL) != SQLITE_OK)
	{
		ErrorLog("[%s] - Failed exec Query[%s]", __FUNCTION__, strQuery);
		return false;
	}

	return true;
}

bool SQLite::Fetch()
{
	return (sqlite3_step(m_stmt) == SQLITE_ROW) ? true : false;
}

void SQLite::AllocHandle()
{
	m_bHandleOpenCheck = true;
}

void SQLite::FreeHandle()
{
	m_bHandleOpenCheck = false;
	if (m_stmt)
	{
		sqlite3_finalize(m_stmt);
		m_stmt = NULL;
	}
}

bool SQLite::GetData(int nFieldNum, char* result)
{
	if (m_stmt == NULL) return false;

	*result = (char)(atoi((const char*)sqlite3_column_text(m_stmt, nFieldNum)));

	return 1;
}

bool SQLite::GetData(int nFieldNum, unsigned char* result)
{
	if (m_stmt == NULL) return 0;

	*result = (unsigned char)(atoi((const char*)sqlite3_column_text(m_stmt, nFieldNum)));

	return true;
}

bool SQLite::GetData(int nFieldNum, short* result)
{
	if (m_stmt == NULL) return 0;

	*result = (short)(sqlite3_column_int(m_stmt, nFieldNum));

	return true;
}

bool SQLite::GetData(int nFieldNum, unsigned short* result)
{
	if (m_stmt == NULL) return false;

	*result = (unsigned short)(sqlite3_column_int(m_stmt, nFieldNum));

	return 1;
}

bool SQLite::GetData(int nFieldNum, int* result)
{
	if (m_stmt == NULL) return false;

	*result = sqlite3_column_int(m_stmt, nFieldNum);

	return true;
}

bool SQLite::GetData(int nFieldNum, unsigned int* result)
{
	if (m_stmt == NULL) return false;

	*result = (unsigned int)sqlite3_column_int(m_stmt, nFieldNum);

	return true;
}

bool SQLite::GetData(int nFieldNum, unsigned long long* result)
{
	if (m_stmt == NULL) return false;

	*result = sqlite3_column_int64(m_stmt, nFieldNum);

	return true;
}

bool SQLite::GetData(int nFieldNum, long long* result)
{
	if (m_stmt == NULL) return false;

	*result = sqlite3_column_int64(m_stmt, nFieldNum);

	return true;
}


bool SQLite::GetData(int nFieldNum, double* result)
{
	if (m_stmt == NULL) return false;

	*result = sqlite3_column_double(m_stmt, nFieldNum);

	return true;
}

bool SQLite::GetData(int nFieldNum, char* const result, unsigned int nSize) // IN: limit OUT : actual size
{
	if (m_stmt == NULL) return false;
	unsigned int length = sqlite3_column_bytes(m_stmt, nFieldNum);

	if (nSize < length)
	{
		ErrorLog("[%s] - >*** Buffer size is too small : org size=[%d] cur size=[%d]. In GetData()***", __FUNCTION__, nSize, length);
		length = nSize;
	}

	memcpy(result, (char*)sqlite3_column_text(m_stmt, nFieldNum), length);

	return true;
}

int SQLite::GetDataBytea(int nFieldNum, unsigned char* const result, unsigned int nSize)
{
	unsigned int length = sqlite3_column_bytes(m_stmt, nFieldNum);
	unsigned char* szBuffer = (unsigned char*)malloc(length + 1);
	if (!szBuffer)
		return 0;

	if (!GetData(nFieldNum, (char* const)szBuffer, (size_t)(length + 1)))
	{
		free(szBuffer);
		return 0;
	}

	int nRetSize = TextToBinary(szBuffer, strlen((const char*)szBuffer), result, nSize);
	free(szBuffer);

	if ((size_t)nRetSize != nSize)
	{
		return 0;
	}

	return nRetSize;
}

int SQLite::SetDataBytea(const unsigned char* bintext, size_t binlen, unsigned char* rettext, size_t retlen)
{
	return BinaryToText(bintext, binlen, rettext, retlen);
}

void SQLite::DisplayErrorMsg()
{
	ErrorLog("[%s] - DB Error. reason = %s", __FUNCTION__, sqlite3_errmsg(m_pDB));

	return;
}
