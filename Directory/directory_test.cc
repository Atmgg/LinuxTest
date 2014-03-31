#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <iostream>
#include <log4cpp/Category.hh>
#include <log4cpp/FileAppender.hh>
#include "Directory.h"
#include "Comm/Global.h" 

using namespace LinuxTest;
using namespace std;

int main(int argc,char *argv[])
{
	// open Log file
	log4cpp::Appender *appender2 = new log4cpp::FileAppender( "default", LOG_PATH );
	appender2->setLayout(new log4cpp::BasicLayout());
	log4cpp::Category& cat1 = log4cpp::Category::getInstance(std::string("directory_test"));
	cat1.addAppender(appender2);

	Cdirectory oDirct;

	char SPathBuf[PATH_MAX];
	char *psd = SPathBuf;
	
	// GetCwd Test
	int ret = oDirct.GetCwd(psd);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat1, GetCwd, ret);

	cat1.info("the PWD is:[%s]", psd);

	// SetDir test
	ret = oDirct.SetDir("/tmp");
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat1, SetDir, ret);

	ret = oDirct.GetCwd(psd);
	cat1.info("the new PWD now is:[%s]", psd);

	// MkDir test
	ret = oDirct.MkDir("/tmp/newdir/");
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat1, Mkdir, ret);
	cat1.info("mkdir dir /tmp/nwedir successful");


	// CreatSymLink test
	ret = oDirct.CreatSymLink("/tmp/newdir/", "/tmp/l_newdir");
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat1, CreatSymLink, ret);
	cat1.info("creat symbolic link  /tmp/l_newdir to /tmp/nwedir successful");

	// RmSymLink test
	ret = oDirct.RmSymLink("/tmp/l_newdir");
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat1, RmSymLink, ret);
	cat1.info("rm symbolic link to /tmp/l_nwedir successful");

	// ChangeName test
	ret = oDirct.ChangeDirName("/tmp/newdir/", "/tmp/newdir2");
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat1, ChangeDirName, ret);
	cat1.info("rename dir /tmp/nwedir to /tmp/newdir2 successful");
	
	// RmDir test
	ret = oDirct.RmDir("/tmp/newdir2/");
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat1, Rmdir, ret);
	cat1.info("rm dir /tmp/nwedir2 successful");

	// ListDir test
	vector<dirent> list;
	oDirct.ListDir(list);


	vector<string> DirNameList;
	oDirct.ListDirName(DirNameList);
	for ( vector<string>::iterator iter1 = DirNameList.begin(); iter1!=DirNameList.end(); ++iter1 )
		cat1.info("%s", (*iter1).c_str() );


	log4cpp::Category::shutdown();

	return 0;
}

