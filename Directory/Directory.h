#ifndef _CDIRECTORY_H_
#define _CDIRECTORY_H_

#include <dirent.h>
#include <vector>

namespace LinuxTest
{

typedef struct TagDircetoryImpl
{
	char sPwd[256];
	DIR* pDIR;
}DirectoryImpl;

class Cdirectory
{
	public:
		Cdirectory();
		virtual ~Cdirectory();

		int GetCwd(char* &pwd);
		int SetDir(const char *path);
		int MkDir(const char *newpath);
		int ReadDir(dirent* &ps_dir); // read a direct set in the path
		int ListDir(std::vector<dirent> &list);
		int ListDirName(std::vector<std::string> &list);
		int RmDir(const char *path); // path must be an empty dir
		int ChangeDirName(const char *oldpath, const char *newpath);
		int CreatSymLink(const char *path, const char *sympath);
		int RmSymLink(const char *sympath);
		// int CreatHardLink(const char *path, const char *newpath);
		// int RmHardLink(const char *path);
	private:
		int Unlink(const char *linkpath);
		int OpenDir();
		int CloseDir();
		Cdirectory(Cdirectory &rhs);
		const Cdirectory&  operator= (Cdirectory &rhs);
	private:
		DirectoryImpl m_Impl;

};

}

#endif
