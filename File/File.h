#ifndef _FILE_H_
#define _FILE_H_

#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <unistd.h>
#include <dirent.h>

namespace LinuxTest
{
typedef struct
{
	int  iFd;
	bool IsOpen;
	char strPath[PATH_MAX+NAME_MAX];
}FileImpl;
class CFile
{
	public:
		CFile();
		virtual ~CFile();
		int Init(const char* path);
		int Clear();
		int Open( const char* path, int flag=O_CREAT|O_RDWR, int mode = 0744);
		int Read(void *buf, size_t count, size_t &iActualCount);
		int Write(const void *buf, size_t count, size_t &iActualCount);
		int Close();
		int Remove();
		int GetStat(struct stat* pStat);
		int GetFileSize(int &iFileSize);
		int GetLastChangeTime(time_t &sLastChangeTime);
		int GetLastAccessTime(time_t &sLastAccessTime);
		int GetLinkCount(nlink_t &iLinkt);
		int GetModeStr(char *strModeStr);
		int SetMode(mode_t iMode);
		int GetOwner(char *strOwnerName);
		int SetOwner(char *strOwnerName);
		int GetGroup(char *strGroupName);
		int SetGroup(char *strGroupName);
		int SetName(const char *pstrName);

	private:
		CFile(const CFile &rhs);
		const CFile& operator=(const CFile &rhs);
		bool IsFileExist(const char* path);
		FileImpl m_Impl;
};

}
#endif
