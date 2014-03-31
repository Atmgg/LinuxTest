/************************************************************************/
/* �����ƣ�  CLog
* �����ռ䣺��
* �ļ�����  Log.h  Log.cpp
* ����ʱ��: 2013-9-9
* ���ߣ�    �����ˣ�754046151��
* ��˵����  ��־��¼��  ����û��ʹ��winapiʵ�� ������linux�н���ʹ��                                             
************************************************************************/

#ifndef LOG_INCLUDE_H
#define LOG_INCLUDE_H

#define LOG_LINE_MAX 1024   //��־��������ַ�����

#include <fstream>

using std::string;
using std::fstream;
using std::ios;

enum LOG_LEVEL     // ��־����
{
	LL_ERROR = 1,              
	LL_WARN = 2,               
	LL_INFORMATION = 3         
};

class CLog
{

public:
    CLog(void):m_openSuccess(false), m_LogLevel(LL_ERROR), m_showLogFlag(true), 
		m_maxLogFileSize(10 * 1024 *1024)
    {
    }
    CLog(const char *filePath, LOG_LEVEL level = LL_ERROR);
    virtual ~CLog(void)
    {
        if (m_openSuccess)
        {
			CloseLogFile();
        }
    }

	// ����־�ļ�
    void OpenLogFile(const char *pFilePath, LOG_LEVEL level = LL_ERROR);
	// д��־����
    void WriteLog(LOG_LEVEL level, const char *pLogText, ...);
    void WriteLog(string logText, LOG_LEVEL level = LL_ERROR);
    void WriteLog(const char *pLogText, LOG_LEVEL level = LL_ERROR);
    void WriteLogEx(LOG_LEVEL level, const char *pLogText, ...);
	// �õ���־�ļ���С
	size_t GetLogFileSize();
	// �����־�ļ�����
	void ClearLogFile();
	void CloseLogFile();

    void SetLogLevel(LOG_LEVEL level = LL_ERROR)
    {
        m_LogLevel = level;
    }
    LOG_LEVEL GetLogLevel() const
    {
        return m_LogLevel;
    }

    void SetShowFlag(bool flag = true)
    {
        m_showLogFlag = flag;
    }
    bool GetShowFlag() const
    {
        return m_showLogFlag;
    }

    void SetMaxLogFileSize(size_t size)
    {
        m_maxLogFileSize = size;
    }
    size_t GetMaxLogFileSize() const
    {
        return m_maxLogFileSize;
    }

    string& GetLogFilePath()
    {
        return m_logFilePath;
    }

    // ��ô��ļ��Ƿ�ɹ��ı�ʶ
    bool GetOpenStatus() const
    {
        return m_openSuccess;
    }

protected:
    string ConvertToRealLogText(const char *pLogText, LOG_LEVEL level = LL_ERROR);
    const std::string &StringFormat(std::string &srcString, const char *pFormatString, ...);
protected:
    fstream m_fileOut;
    bool m_openSuccess;  // ��־�ļ���״̬ true��ʾ�Ѿ��ɹ��� ����û�д�
	string m_logFilePath; // ��־�ļ�����·�� string����

protected:
    LOG_LEVEL m_LogLevel;  // ��־��¼���� Ĭ��ΪLL_ERROR
	bool m_showLogFlag;    // ��ʾ��־��־  Ĭ��Ϊtrue
	size_t m_maxLogFileSize; // ��־�ļ�����С �����ô�С����ɾ�� Ĭ��Ϊ10MB
};

#endif

