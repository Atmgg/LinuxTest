#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>
#include "Comm/Global.h"
#include "Directory.h"

using namespace LinuxTest;
using namespace std;

Cdirectory::Cdirectory()
{
	memset( &m_Impl,0,sizeof(m_Impl) );
	char Stmp[PATH_MAX];
	char *pStr = Stmp;
	GetCwd(pStr);
	SetDir(pStr);
}
Cdirectory::~Cdirectory()
{

}

int Cdirectory::GetCwd(char* &pwd) // deep copy
{
	char sBuf[PATH_MAX];
	if ( 0 == strlen(m_Impl.sPwd) )
	{
		getcwd(&sBuf[0], PATH_MAX);
		if (!sBuf)
		{
			return errno;
		}
		else
		{
			strncpy( pwd, sBuf, PATH_MAX+1 );
			return SUCCEED;
		}
	}
	else
	{
		strncpy(pwd, m_Impl.sPwd,strlen(m_Impl.sPwd)+1 );
		return SUCCEED;
	}
}

int Cdirectory::SetDir(const char *path)
{
	if (NULL == path)
		return ERR_NULL_POINTER;

	if ( -1 == chdir(path) )
		return errno;
	
	strncpy(m_Impl.sPwd, path, strlen(path)+1 );
	return SUCCEED;
}

int Cdirectory::MkDir(const char *newpath)
{
	if (NULL == newpath)
		return ERR_NULL_POINTER;

	if ( -1 == mkdir(newpath, 0744) )
		return errno;
	
	return SUCCEED;
}

int Cdirectory::RmDir(const char *path)
{
	if (NULL == path)
		return ERR_NULL_POINTER;

	if ( -1 == rmdir(path) )
		return errno;
	
	return SUCCEED;
}

int Cdirectory::ChangeDirName(const char *oldpath, const char *newpath)
{
	if (!oldpath || !newpath)
		return ERR_NULL_POINTER;

	if ( -1 == rename(oldpath, newpath) )
		return errno;

	return SUCCEED;
}

int Cdirectory::CreatSymLink(const char *path, const char *sympath)
{
	if (!path || !sympath)
		return ERR_NULL_POINTER;

	if ( -1 == symlink(path, sympath) )
		return errno;

	return SUCCEED;
}

/* linux doesn't allow to creat hard link to a dir
int Cdirectory::CreatHardLink(const char *path, const char *newpath)
{
	if (!path || !newpath)
		return ERR_NULL_POINTER;

	if ( -1 == link(path, newpath) )
		return errno;

	return SUCCEED;
}

int Cdirectory::RmHardLink(const char *path)
{
	return Unlink(path);
}
*/

int Cdirectory::Unlink(const char *linkpath)
{
	if (!linkpath)
		return ERR_NULL_POINTER;

	if ( -1 == unlink(linkpath) )
		return errno;

	return SUCCEED;
}

int Cdirectory::RmSymLink(const char *sympath)
{
	return Unlink(sympath);
}


int Cdirectory::OpenDir()
{
	if ( 0 == strlen(m_Impl.sPwd) )
		return ERR_ILEAGAL_CLASS_MEMBER;

	m_Impl.pDIR = opendir(m_Impl.sPwd);

	return (!m_Impl.pDIR) ? errno : SUCCEED ;
}

int Cdirectory::CloseDir()
{
	if (!m_Impl.pDIR)
		return SUCCEED;

	if ( -1 == closedir(m_Impl.pDIR) )
		return errno;
	else
	{
		m_Impl.pDIR = NULL;
		return SUCCEED;
	}
}

int Cdirectory::ReadDir( dirent* &ps_dir )
{
	int ret = OpenDir();
	if ( SUCCEED != ret )
		return ret;

	ps_dir = readdir(m_Impl.pDIR);
	if ( !ps_dir )
		return errno;

	return CloseDir();
}

int Cdirectory::ListDir(vector<dirent> &list)
{
	int ret = OpenDir();
	if ( SUCCEED != ret )
		return ret;

	dirent* pdir = NULL;
	dirent s_dir;
	int errno_old = errno;
	while (1) 
	{
		pdir = readdir(m_Impl.pDIR);
		if ( !pdir )
		{
			if (errno_old == errno)
				break;
			else
				return errno;
		}

		s_dir = *pdir;
		list.push_back(s_dir);
	}

	return CloseDir();
}

int Cdirectory::ListDirName(std::vector<std::string> &list)
{
	vector<dirent> vList;
	int ret = ListDir(vList);
	if (SUCCEED != ret)
		return ret;
	
	string strTmp;
	for ( vector<dirent>::iterator iter1 = vList.begin(); iter1!=vList.end(); ++iter1 )
	{
		strTmp = iter1->d_name;
		list.push_back(strTmp);
	}

	return SUCCEED;
}
