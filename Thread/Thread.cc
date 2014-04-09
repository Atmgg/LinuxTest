#include <pthread.h>
#include <errno.h>
#include <memory.h>
#include <assert.h>
#include "Thread.h"
#include "Comm/Global.h"

using namespace std;
using namespace LinuxTest;

CThread::CThread()
{
	memset(&m_Impl, 0, sizeof(m_Impl) );
}

CThread::~CThread()
{
}

void* CThread::pthread_func(void* arg)
{
	assert (arg != NULL);

	CThread* _thread = static_cast<CThread*>(arg);

	_thread->m_Impl.isThreadRun = true;
	_thread->m_Impl.iRunFunRet = _thread->Run(_thread->m_Impl.arg);
	_thread->m_Impl.isThreadRun = false;

	return &_thread->m_Impl.iRunFunRet;
}

int CThread::Start(void *arg)
{
	if (m_Impl.isThreadRun)
		return ERR_THREAD_IS_RUNNING;

	m_Impl.arg = arg;
	int ret = pthread_create( &(m_Impl.thread), NULL, pthread_func, this);
	if ( 0 != ret )
		return errno;
	else 
		m_Impl.isCreatThreadSucceed = true;

	return SUCCEED;
}

int CThread::Join()
{
	int iret; 
	int* pret = &iret;
	pthread_join(m_Impl.thread, (void**)&pret);
	return iret;
}
