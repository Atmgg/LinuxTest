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
		int Open( const char* path, int flag=O_CREAT|O_RDWR, int mode = 0744);
		int Close();
		int GetStat(struct stat* pStat);
		int GetFileSize(int &iFileSize);
		int GetLastChangeTime(time_t &sLastChangeTime);
		int GetLastAccessTime(time_t &sLastAccessTime);
		int GetOwner(char *strOwnerName);
		int GetGroup(char *strGroupName);

	private:
		CFile(const CFile &rhs);
		const CFile& operator=(const CFile &rhs);
		FileImpl m_Impl;
};

}
#endif
