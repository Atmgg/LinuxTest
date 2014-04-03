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

	// Init Test
	int ret = file1.Init(strName);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, Init, ret);
	cat.info("Init File [%s] succeed", strName);

	// Open Test
	ret = file1.Open(&strName[0]);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, Open, ret);
	cat.info("Open File [%s] succeed", strName);

	//Write Test
	char strBuf[200];
	strncpy(strBuf, "a white cat", strlen("a white cat")+1);
	size_t iSize = 0;
	ret = file1.Write(&strBuf[0], strlen("a white cat")+1, iSize);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, Write, ret);
	cat.info("write File [%s] str [%s] succeed", strName, strBuf);

	// Read Test
	ret = file1.Read(&strBuf[0], 7, iSize);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, Read, ret);
	strBuf[7]='\0';
	cat.info("Read 7 chars from File [%s] is [%s]", strName, strBuf);

	// GetFileSize Test
	int iFileSize;
	ret = file1.GetFileSize(iFileSize);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetFileSize, ret);
	cat.info("size of [%s] is [%d]", strName, iFileSize);

	// GetLastChangeTime Test
	time_t sLastChangeTime;
	ret = file1.GetLastChangeTime(sLastChangeTime);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetLastChangeTime, ret);
	cat.info( "Last Change time of [%s] is [%s]", strName, GetCtimeStr(sLastChangeTime) );

	// GetLastAccessTime Test
	time_t sLastAccessTime;
	ret = file1.GetLastAccessTime(sLastAccessTime);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetLastAccessTime, ret);
	cat.info( "Last Access time of [%s] is [%s]", strName, GetCtimeStr(sLastAccessTime) );

	// GetOwner Test
	ret = file1.GetOwner(strBuf);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetOwner, ret);
	cat.info( "Owner of [%s] is [%s]", strName, strBuf );

	// SetOwner Test
	strncpy(strBuf, "Tedwang", strlen("Tedwang")+1 );
	ret = file1.SetOwner(strBuf);
	if ( SUCCEED != ret ) 
		PERR_AND_EXIT(cat, SetOwner, ret);
	cat.info( "Set Owner of [%s] to [%s] succeed", strName, strBuf );

	strncpy(strBuf, "wangjingji", strlen("wangjingji")+1 );
	ret = file1.SetOwner(strBuf);
	if ( SUCCEED != ret ) 
		PERR_AND_EXIT(cat, SetOwner, ret);
	cat.info( "recover Owner of [%s] to [%s] succeed", strName, strBuf );

	// GetGroup Test
	ret = file1.GetGroup(strBuf);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetGroup, ret);
	cat.info( "Group of [%s] is [%s]", strName, strBuf );

	// SetGroup Test
	strncpy(strBuf, "sudo", strlen("sudo")+1 );
	ret = file1.SetGroup(strBuf);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, SetGroup, ret);
	cat.info( "Set Group of [%s] to [%s] succeed", strName, strBuf );

	strncpy(strBuf, "wangjingji", strlen("wangjingji")+1 );
	ret = file1.SetGroup(strBuf);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, SetGroup, ret);
	cat.info( "Set Group of [%s] to [%s] succeed", strName, strBuf );

	// SetName Test
	strncpy(strName, "/tmp/file2", strlen("/tmp/file2")+1 );
	ret = file1.SetName(strBuf);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, SetName, ret);
	cat.info( "Set Name of [%s] to [%s] succeed", "/tmp/file1",strName );

	// GetLinkCount Test
	unsigned int iLinkCnt = 0;
	ret = file1.GetLinkCount(iLinkCnt);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetLinkCount, ret);
	cat.info( "Link Count of [%s] is [%d]", strName, iLinkCnt );

	// GetModeStr Test
	ret = file1.GetModeStr(strBuf);
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, GetModeStr, ret);
	cat.info( "Mode String of [%s] is [%s]", strName, strBuf );

	// SetMode Test
	ret = file1.SetMode(0777);
	if (SUCCEED != ret)
		PERR_AND_EXIT(cat, SetMode, ret);
	cat.info("SetMode of [%s] to [%o] succeed", strName, 0777);

	// Close Test
	ret = file1.Close();
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, Close, ret);
	cat.info("Close File [%s] succeed", strName);

	// Remvoe Test
	ret = file1.Remove();
	if ( SUCCEED != ret )
		PERR_AND_EXIT(cat, Remove, ret);
	cat.info("Remove File [%s] succeed", strName);
	
	exit(0);
}
