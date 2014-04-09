#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

namespace LinuxTest
{

typedef struct 
{
	pthread_t thread;
	void *arg; // void pointer point to thread func args
	int iRunFunRet;
	bool isCreatThreadSucceed;
	bool isThreadRun;
	
}CThreadImpl;

class CThread
{
	public:
		static void* pthread_func(void* arg );
		CThread();
		virtual ~CThread();
		int Start(void *arg = NULL);
		virtual int Run(void *arg=0) = 0;
		int Join();
	private:
		CThread(const CThread &cms);
		const CThread& operator= (CThread &rhs);

		CThreadImpl m_Impl;
};

}

#endif
