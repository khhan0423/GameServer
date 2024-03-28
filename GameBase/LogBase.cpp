#include "pch.h"
#include "LogBase.h"
#include <time.h>
#include <direct.h>

GameLog::~GameLog()
{
	if (m_pFile) fclose(m_pFile);
}

void GameLog::Init(const __int32 iLevel, const __int32 iOutput, const std::string& strFilePath)
{
	{
		if (iLevel < GAMELOG_LEVEL_DEBUG) const_cast<__int32&>(iLevel) = GAMELOG_LEVEL_DEBUG;
		if (iLevel > GAMELOG_LEVEL_SYSTEM) const_cast<__int32&>(iLevel) = GAMELOG_LEVEL_SYSTEM;

		m_iLevel = iLevel;
		m_iOutput = iOutput;

		m_strFilePath = strFilePath;
	}
}

void GameLog::Log(const __int32 iLevel, const char* strFile, const __int32 iLine, const char* strFormat, ...)
{
#pragma  TODO ("C++ 스타일로 언젠가 변경할것")
	{
		std::lock_guard<std::mutex> _lock(m_Lock);

		if (m_iOutput == GAMELOG_OUTPUT_NONE || iLevel < m_iLevel) return;

		time_t _time;
		time(&_time);

		struct tm Tm;
		if (localtime_s(&Tm, &_time)) return;

		char _strTime[32];
		strftime(_strTime, 32, "%Y-%m-%d %H:%M:%S", &Tm);

		va_list	_args;
		va_start(_args, strFormat);

		if (m_iOutput == GAMELOG_OUTPUT_SCRN || m_iOutput == GAMELOG_OUTPUT_BOTH)
		{
			printf("%s:", _strTime);
			vprintf(strFormat, _args);
			printf("\n");
		}
		if (m_iOutput == GAMELOG_OUTPUT_FILE || m_iOutput == GAMELOG_OUTPUT_BOTH)
		{
			if (m_pFile && m_iCount > MAX_LOG_COUNT)
			{
				fclose(m_pFile);
				m_pFile = nullptr;
				m_iCount = 0;
			}

			if (!m_pFile)
			{
				char _strLogFile[256];
				sprintf_s(_strLogFile, sizeof(_strLogFile), "%s\\%s(%d)", GAMELOG_PATH, m_strFilePath.c_str(), 0);
				strftime(_strLogFile + strlen(_strLogFile), 64, "_%Y-%m-%d_%H-%M-%S.log", &Tm);
				m_strLogFile = _strLogFile;

				std::ignore = _mkdir(GAMELOG_PATH);

				m_pFile = _fsopen(m_strLogFile.c_str(), "a+", _SH_DENYNO);
				if (!m_pFile) return;
			}

			fprintf(m_pFile, "LEVEL[%d] : %s : ", iLevel, _strTime);
			vfprintf(m_pFile, strFormat, _args);
			fprintf(m_pFile, " - %s(%d)\n", strFile, iLine);

			fflush(m_pFile);
		}

		m_iCount++;

		va_end(_args);
	}
}