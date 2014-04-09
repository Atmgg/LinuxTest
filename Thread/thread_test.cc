#include <stdlib.h>
#include <log4cpp/Category.hh>
#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <log4cpp/FileAppender.hh>
#include "Comm/Global.h"
#include "Thread.h"

using namespace std;
using namespace LinuxTest;

class CTestThread :public CThread
{
	virtual int Run(void* arg)
	{
		if(NULL == arg)
			return ERR;

		int *pint = (int *)arg;
		for(int i=0;i<5;++i)
		{
			cout << "this is thread "<<*pint<<endl;
			sleep(1);
		}
		return SUCCEED;
	};

};

int main(int argc, char* argv[])
{
	// open Log file
	log4cpp::Appender *appender = new log4cpp::FileAppender( "default", LOG_PATH );
	appender->setLayout(new log4cpp::BasicLayout());
	log4cpp::Category& cat = log4cpp::Category::getInstance(std::string("thread_test"));
	cat.addAppender(appender);

	CTestThread thread1, thread2;

	int iret = thread1.SetAttrScope(PTHREAD_SCOPE_SYSTEM);
	int iTmp = -1;
	if (SUCCEED != iret)
	{
		PERR_AND_EXIT(cat, thread1.SetAttrScope, iret);
	}
	else
	{
		iret = thread1.GetAttrScope(iTmp);
		cat.info("scope state of thread1 is [%d]", iTmp);
	}

	thread1.SetAttrGuardSize(8*1024);
	if (SUCCEED != iret)
	{
		PERR_AND_EXIT(cat, thread1.SetAttrGuardSize, iret);
	}
	else
	{
		size_t uiSize = 0;
		iret = thread1.GetAttrGuardSize(uiSize);
		cat.info("guard size of thread1 is [%d] KB", uiSize/1024);
	}

	thread1.SetAttrInherit(PTHREAD_EXPLICIT_SCHED) ;
	if (SUCCEED != iret)
	{
		PERR_AND_EXIT(cat, thread1.SetAttrInherit, iret);
	}
	else
	{
		iret = thread1.GetAttrInherit(iTmp);
		cat.info("inherit state of thread1 is [%d]", iTmp);
	}

	thread1.SetAttrSchedPolicy(SCHED_RR);
	if (SUCCEED != iret)
	{
		PERR_AND_EXIT(cat, thread1.SetAttrSchedPolicy, iret);
	}
	else
	{
		iret = thread1.GetAttrSchedPolicy(iTmp);
		cat.info("schedule state of thread1 is [%d]", iTmp);
	}

	size_t iStackSize = 0;
	iret = thread1.GetStackSize(iStackSize);
	if (SUCCEED != iret)
	{
		PERR_AND_EXIT(cat, thread1.GetAttrStackSize, iret);
	}
	else
	{
		cat.info("stack size of thread1 is [%d] KB",iStackSize/1024);
	}

	iret = thread1.SetStackSize(iStackSize*2);
	if (SUCCEED != iret)
		PERR_AND_EXIT(cat, thread1.SetAttrStackSize, iret);

	int thread_num1 = 1;
	int thread_num2 = 2;

	iret = thread1.Start(&thread_num1);
	if(SUCCEED != iret)
		PERR_AND_EXIT(cat, thread1.Start, iret);

	iret = thread2.Start(&thread_num2);
	if(SUCCEED != iret)
		PERR_AND_EXIT(cat, thread2.Start, iret);

	cat.info("is thread1 equals thread2 [%c]", (thread1==thread2? 'Y': 'N') );

	sleep(2);
	iret = CThread::SendCanCel(thread2);
	if(SUCCEED != iret)
	{
		PERR_AND_EXIT(cat, CThread::SendCanCel, iret);
	}
	else
	{
		cat.info("send cancel signal to thread2  succeed");

	}

	iret = CThread::Join(thread1);
	iret = CThread::Join(thread2);

	cat.info("join both thread1 and thread2 succeed");

	exit(0);
}
