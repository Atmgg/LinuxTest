#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <iostream>
#include <log4cpp/Category.hh>
#include <time.h>
#include <log4cpp/FileAppender.hh>
#include "File.h"
#include "Comm/Global.h" 


using namespace LinuxTest;
using namespace std;

static char TimeBuff[20];
const char* GetCtimeStr(time_t sTime)
{
	char *pStr = ctime(&sTime);
	int len = strlen(pStr);
	strncpy( TimeBuff, pStr, len-1 );
	TimeBuff[len]='\0';

	return TimeBuff;
}

int main(int argc, char *argv[])
{
	// open Log file
	log4cpp::Appender *appender = new log4cpp::FileAppender( "default", LOG_PATH );
	appender->setLayout(new log4cpp::BasicLayout());
	log4cpp::Category& cat = log4cpp::Category::getInstance(std::string("file_test"));
	cat.addAppender(appender);

	CFile file1;
	char strName[] = "/tmp/file1";

	int ret = file1.Open(&strName[0]);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, Open, ret);

	cat.info("Open File [%s] succeed", strName);

	int iFileSize;
	ret = file1.GetFileSize(iFileSize);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetFileSize, ret);
	cat.info("size of [%s] is [%d]", strName, iFileSize);


	time_t sLastChangeTime;
	ret = file1.GetLastChangeTime(sLastChangeTime);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetLastChangeTime, ret);
	cat.info( "Last Change time of [%s] is [%s]", strName, GetCtimeStr(sLastChangeTime) );


	time_t sLastAccessTime;
	ret = file1.GetLastAccessTime(sLastAccessTime);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetLastAccessTime, ret);
	cat.info( "Last Access time of [%s] is [%s]", strName, GetCtimeStr(sLastAccessTime) );

	char strBuf[200];
	ret = file1.GetOwner(strBuf);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetOwner, ret);
	cat.info( "Owner of [%s] is [%s]", strName, strBuf );

	ret = file1.GetGroup(strBuf);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetGroup, ret);
	cat.info( "Group of [%s] is [%s]", strName, strBuf );

	ret = file1.Close();
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, Close, ret);

	cat.info("Close File [%s] succeed", strName);
	
	exit(0);
}
