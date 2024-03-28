#include "pch.h"
#include <sqlite3.h>
#include "SQLiteConnet.h"
#include "LogBase.h"

using namespace DataBase::SQLite3;

int busy_handler(void* /*pArg*/, int nCallCount)
{
	if (nCallCount < MAX_BUSY_WAIT_COUNT)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(MAX_BUSY_WAIT_TIME));
		return 1;
	}
	return 0;
}

SQLiteConnector::SQLiteConnector() : m_DBHandlerPtr(nullptr), m_isOpen(false)
{
}

SQLiteConnector::~SQLiteConnector()
{
	Close();
}

bool SQLiteConnector::InitDBName(const std::string& DBfileName)
{
	m_DBFileName = DBfileName;
	return true;
}

sqlite3* SQLiteConnector::GetHandle()
{
	return m_DBHandlerPtr;
}

bool SQLiteConnector::IsOpen()
{
	return m_isOpen;
}

bool SQLiteConnector::Open()
{
	return TryOpen();
}

bool SQLiteConnector::TryOpen()
{
	if (IsOpen())
		Close();

	//커넥션 풀세팅하여 여러개의 db 커넥션을 가질 경우 SQLITE_OPEN_SHAREDCACHE 세팅해 주어야 한다.
	int nError = sqlite3_open_v2(m_DBFileName.c_str(), &m_DBHandlerPtr, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE | SQLITE_OPEN_SHAREDCACHE, NULL);
	if (nError != SQLITE_OK)
	{
		ErrorLog("[%s] - Open Sqlite[%s] is Failed : Code(%d)", __FUNCTION__, m_DBFileName.c_str(), nError);
		return false;
	}
	//커넥션 풀세팅하여 여러개의 db 커넥션을 가질 경우 SQLITE_CONFIG_MULTITHREAD 세팅해 주어야 한다.
	sqlite3_db_config(m_DBHandlerPtr, SQLITE_CONFIG_MULTITHREAD);
	sqlite3_busy_timeout(m_DBHandlerPtr, 20);

	if (sqlite3_busy_handler(m_DBHandlerPtr, busy_handler, NULL) != SQLITE_OK)
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

	if (sqlite3_exec(m_DBHandlerPtr, PragmaString.c_str(), NULL, NULL, NULL) != SQLITE_OK)
	{
		ErrorLog("[%s] PragmaString Failed", __FUNCTION__);
		return false;
	}

	//vacuum 은 패스
	//if (sqlite3_exec(m_DBHandlerPtr, "vacuum;", NULL, NULL, NULL) != SQLITE_OK)
	//{
	//	ErrorLog("[%s] vacuum Failed", __FUNCTION__);
	//	return false;
	//}

	m_isOpen.exchange(true);

	return true;
}

void SQLiteConnector::Close()
{
	m_isOpen.exchange(false);

	if (m_DBHandlerPtr == nullptr)
		return;

	if(sqlite3_close(m_DBHandlerPtr) != SQLITE_OK)
		ErrorLog("[%s] Close Failed", __FUNCTION__);

	m_DBHandlerPtr = nullptr;
}