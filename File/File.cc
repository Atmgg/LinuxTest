#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <memory.h>
#include <fcntl.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <errno.h>
#include <memory.h>
#include <string.h>
#include "Comm/Global.h"
#include "File.h"

using namespace LinuxTest;
using namespace std;

CFile::CFile()
{
	memset( &m_Impl, 0, sizeof(m_Impl) );
}

CFile::~CFile()
{
}


int CFile::Open( const char* path, int flags, int mode )
{
	if (!path)
		return ERR_NULL_POINTER;

	memcpy(m_Impl.strPath, path, strlen(path)+1);

	int iFd = open(path,flags, mode);
	if (-1 == iFd )
		return errno;
	m_Impl.iFd = iFd;
	m_Impl.IsOpen = true;

	return SUCCEED;
}

int CFile::Close()
{
	if (!m_Impl.IsOpen)
		return SUCCEED;
	int ret = close(m_Impl.iFd);
	return (!ret ?errno :SUCCEED);
}

int CFile::GetStat(struct stat* pStat)
{
	if (!m_Impl.IsOpen)
		return ERR_ILEAGAL_CLASS_MEMBER;

	if ( !fstat(m_Impl.iFd, pStat) )
		return errno;

	return SUCCEED;
}

int CFile::GetFileSize(int &iFileSize)
{
	struct stat sStat;
	int ret = GetStat(&sStat);
	if (SUCCEED != ret)
		return ret;
	
	iFileSize = sStat.st_size;
	return SUCCEED;
}


int CFile::GetLastChangeTime(time_t &sLastChangeTime)
{
	struct stat sStat;
	int ret = GetStat(&sStat);
	if (SUCCEED != ret)
		return ret;
	
	sLastChangeTime = sStat.st_mtime;
	return SUCCEED;
}

int CFile::GetLastAccessTime(time_t &sLastAccessTime)
{
	struct stat sStat;
	int ret = GetStat(&sStat);
	if (SUCCEED != ret)
		return ret;

	sLastAccessTime = sStat.st_atime;
	return SUCCEED;
}

int CFile::GetOwner(char *strOwnerName)
{
	struct stat sStat;
	int ret = GetStat(&sStat);
	if (SUCCEED != ret)
		return ret;
	
	int errno_old = errno;
	struct passwd* psPass = getpwuid(sStat.st_uid);
	if(!psPass)
		return (errno_old == errno ? errno : ERR_NO_MATCH_UID);
	
	strncpy( strOwnerName, psPass->pw_name, strlen(psPass->pw_name)+1 );
	return SUCCEED;
}


int CFile::GetGroup(char *strGroupName)
{
	struct stat sStat;
	int ret = GetStat(&sStat);
	if (SUCCEED != ret)
		return ret;
	
	int errno_old = errno;
	struct group* psGroup = getgrgid(sStat.st_gid);
	if(!psGroup)
		return (errno_old == errno ? errno : ERR_NO_MATCH_GID);

	strncpy(strGroupName, psGroup->gr_name, strlen(psGroup->gr_name)+1 );
	return SUCCEED;

}


int CFile::GetLinkCount(nlink_t &iLinkt)
{
	struct stat sStat;
	int ret = GetStat(&sStat);
	if (SUCCEED != ret)
		return ret;

	iLinkt = sStat.st_nlink;
	return SUCCEED;
}

int CFile::GetModeStr(char *strModeStr)
{
	struct stat sStat;
	int ret = GetStat(&sStat);
	if (SUCCEED != ret)
		return ret;
	
	strncpy(strModeStr, "----------", 11);
	mode_t iMode = sStat.st_mode;

	if ( S_ISLNK(iMode) )
	{
		strModeStr[0] = 'l';
	}
	else if ( S_ISREG(iMode) )
	{
		strModeStr[0] = '-';
	}
	else if ( S_ISDIR(iMode) )
	{
		strModeStr[0] = 'd';
	}
	else if ( S_ISCHR(iMode) )
	{
		strModeStr[0] = 'c';
	}
	else if ( S_ISFIFO(iMode) )
	{
		strModeStr[0] = 'f';
	}
	else if ( S_ISSOCK(iMode) )
	{
		strModeStr[0] = 's';
	}

	if (iMode&S_IRUSR)
		strModeStr[1] = 'r';
	if (iMode&S_IWUSR)
		strModeStr[2] = 'w';
	if (iMode&S_IXUSR)
		strModeStr[3] = 'x';

	if (iMode&S_IRGRP)
		strModeStr[4] = 'r';
	if (iMode&S_IWGRP)
		strModeStr[5] = 'w';
	if (iMode&S_IXGRP)
		strModeStr[6] = 'x';

	if (iMode&S_IROTH)
		strModeStr[7] = 'r';
	if (iMode&S_IWOTH)
		strModeStr[8] = 'w';
	if (iMode&S_IXOTH)
		strModeStr[9] = 'x';

	return SUCCEED;
}
