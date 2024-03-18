#pragma once
#include <string>
#include "SingletonBase.h"

#define GAMELOG_PATH			"Log"

#define GAMELOG_LEVEL_DEBUG		1
#define GAMELOG_LEVEL_INFO		2
#define GAMELOG_LEVEL_WARNING	3
#define GAMELOG_LEVEL_ERROR		4
#define GAMELOG_LEVEL_SYSTEM	5

#define PLOG_LEVEL_DEBUG		GAMELOG_LEVEL_DEBUG, __FILE__, __LINE__
#define PLOG_LEVEL_INFO			GAMELOG_LEVEL_INFO, __FILE__, __LINE__
#define PLOG_LEVEL_WARNING		GAMELOG_LEVEL_WARNING, __FILE__, __LINE__
#define PLOG_LEVEL_ERROR		GAMELOG_LEVEL_ERROR, __FILE__, __LINE__
#define PLOG_LEVEL_SYSTEM		GAMELOG_LEVEL_SYSTEM, __FILE__, __LINE__

#define GAMELOG_OUTPUT_NONE		0
#define GAMELOG_OUTPUT_SCRN		1
#define GAMELOG_OUTPUT_FILE		2
#define GAMELOG_OUTPUT_BOTH		3

class GameLog
{
private:
	const int	MAX_LOG_COUNT = 100000;

private:
	int			m_iLevel = GAMELOG_LEVEL_DEBUG;
	int			m_iOutput = GAMELOG_OUTPUT_NONE;
	string		m_strFilePath;
	string		m_strLogFile;
	FILE*		m_pFile = nullptr;
	int			m_iCount = 0;
	mutex		m_Lock;

public:
	virtual ~GameLog();

public:
	const std::string& GetLogFile() const { return m_strLogFile; }

public:
	void Init(const __int32 iLevel, const __int32 iOutput, const string& strFilePath);
	void Log(const __int32 iLevel, const char* strFile, const __int32 iLine, const char* strFormat, ...);
};

class SGlobalLog : public GameLog, public TSingleton<SGlobalLog> {};

#define GetGlobalLog()	SGlobalLog::GetInstance()
#define DebugLog(...)	GetGlobalLog()->Log(PLOG_LEVEL_DEBUG, __VA_ARGS__);
#define InfoLog(...)	GetGlobalLog()->Log(PLOG_LEVEL_INFO, __VA_ARGS__);
#define WarningLog(...) GetGlobalLog()->Log(PLOG_LEVEL_WARNING, __VA_ARGS__);
#define ErrorLog(...)	GetGlobalLog()->Log(PLOG_LEVEL_ERROR, __VA_ARGS__);
#define SystemLog(...)	GetGlobalLog()->Log(PLOG_LEVEL_SYSTEM, __VA_ARGS__);