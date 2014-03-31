#ifndef _ILOG_H_
#define _ILOG_H_


namespace LinuxTest
{

enum
{
	LogInfo  = 0,
	LogDebug = 1,
	LogErr   = 2,
};
class CLog
{
	public:
		CLog();
		CLog(const char *psModuleName, int iLevel, const char *psLogPath);
		~CLog();

		void LogErr();
		int  OpenLog(const char *psModuleName, int iLevel, const char *psLogPath);
	private:
		CLog(const CLog &rhs);
		const CLog & operator= (const CLog &rhs);
	private:
		char m_ModuleName[256];
		char m_LogPath[256];
		int  m_Level;
		int  m_Logfd;
}

}
#endif
