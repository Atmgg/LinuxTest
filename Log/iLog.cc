#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "iLog.h"

using namespace LinuxTest

CLog::CLog():
m_Level(LogInfo),
m_Logfd(-1)
{
	strncpy(m_ModuleName,"default.log", strlen("default"));
	strncpy(m_LogPath,"/tmp/log", strlen("/tmp/log"));
}

CLog::CLog(const char *psModuleName, int iLevel, const char *psLogPath)
{
	OpenLog(psModuleName, iLevel, psLogPath);
}

CLog::~CLog()
{
}

int OpenLog(const char *psModuleName, int iLevel, const char *psLogPath)
{
	if (!psModuleName)
		strncpy(m_ModuleName,psModuleName, strlen(psModuleName));
	else
		strncpy(m_ModuleName,"default", strlen("default"));

	if (!psModuleName)
		strncpy(m_LogPath, psLogPath, strlen(psLogPath));
	else
		strncpy(m_LogPath,"/tmp/log", strlen("/tmp/log"));

	m_Level = iLevel;
	m_Logfd = -1;

	if open(psLogPath, )

	return SUCCEED;
}
