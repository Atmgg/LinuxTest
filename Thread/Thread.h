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
	pthread_attr_t thread_attr;
	bool isCreatThreadSucceed;
	bool isThreadRun;
	
}CThreadImpl;

class CThread
{
public:
	CThread();
	virtual ~CThread();
	int Start(void *arg = NULL);
	virtual int Run(void *arg) = 0;
	bool operator==(const CThread &rhs);


	int SetAttrScope(int scope); // Set thread to bind to a light weight process or not
	int GetAttrScope(int& scope);

	int SetAttrDetach(); // set the thread to release all sources after the thread ended
	int GetAttrDetach(int& DetachState);

	int SetAttrPriority(int priority);
	int GetAttrPriority(int &priority);

	int SetAttrGuardSize(size_t size);
	int GetAttrGuardSize(size_t& size);

	int SetAttrInherit(int inheritsched);
	int GetAttrInherit(int& inheritsched);

	int SetAttrSchedPolicy(int policy);
	int GetAttrSchedPolicy(int& policy);

	// to set/get the new thread's stack addr and size
	int SetStack(void *stack, size_t stack_size); 
	int GetStack(void **stack, size_t& stack_size);

	int SetStackSize(size_t stack_size);
	int GetStackSize(size_t& stack_size);

	static int Join(const CThread& rhs);
	static int SendCanCel(const CThread& ThreadToCancel);

private:
	CThread(const CThread &cms);
	const CThread& operator= (CThread &rhs);
	static void* pthread_func(void* arg);
	int InitThreadAttr();
	int DestroyThreadAttr();

	CThreadImpl m_Impl;
};

}

#endif
