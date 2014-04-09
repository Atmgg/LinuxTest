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
	InitThreadAttr();
}

CThread::~CThread()
{
	DestroyThreadAttr();
}

void* CThread::pthread_func(void* arg)
{
	assert (arg != NULL);

	CThread* _thread = static_cast<CThread*>(arg);

	_thread->m_Impl.isThreadRun = true;
	_thread->m_Impl.iRunFunRet = _thread->Run(_thread->m_Impl.arg);
	_thread->m_Impl.isThreadRun = false;

	// return &_thread->m_Impl.iRunFunRet; // the same as pthread_exit() call
	pthread_exit(&_thread->m_Impl.iRunFunRet);
}

int CThread::Start(void *arg)
{
	if (m_Impl.isThreadRun)
		return ERR_THREAD_IS_RUNNING;

	m_Impl.arg = arg;
	int ret = pthread_create( &(m_Impl.thread), &m_Impl.thread_attr, pthread_func, this);
	if ( 0 != ret )
		return errno;
	else 
		m_Impl.isCreatThreadSucceed = true;

	return SUCCEED;
}

int CThread::Join(const CThread& rhs)
{
	int iret = SUCCEED; 
	int* pret = &iret;
	pthread_join(rhs.m_Impl.thread, (void**)&pret);
	return iret;
}

int CThread::InitThreadAttr()
{
	return pthread_attr_init(&m_Impl.thread_attr);
}

int CThread::DestroyThreadAttr()
{
	return pthread_attr_destroy(&m_Impl.thread_attr);
}

int CThread::SetAttrScope(int scope)
{
	return  pthread_attr_setscope(&m_Impl.thread_attr, scope);
}

int CThread::GetAttrScope(int& scope)
{
	return pthread_attr_getscope(&m_Impl.thread_attr, &scope);
}

int CThread::SetAttrDetach()
{
	return pthread_attr_setdetachstate(&m_Impl.thread_attr, PTHREAD_CREATE_DETACHED);
}

int CThread::GetAttrDetach(int &DetachState)
{
	return pthread_attr_getdetachstate(&m_Impl.thread_attr, &DetachState);
}

int CThread::SetAttrPriority(int priority)
{
	sched_param parm;
	pthread_attr_getschedparam(&m_Impl.thread_attr, &parm); // on linux this function is always succeed
	parm.sched_priority = priority;
	pthread_attr_setschedparam(&m_Impl.thread_attr, &parm);  // on linux this function is always succeed

	return SUCCEED;
}

int CThread::GetAttrPriority(int &priority)
{
	sched_param parm;
	pthread_attr_getschedparam(&m_Impl.thread_attr, &parm);
	priority = parm.sched_priority;

	return SUCCEED;
}

int CThread::SetAttrGuardSize(size_t size)
{
	return pthread_attr_setguardsize(&m_Impl.thread_attr, size);
}

int CThread::GetAttrGuardSize(size_t& size)
{
	return pthread_attr_getguardsize(&m_Impl.thread_attr, &size);
}

int CThread::SetAttrInherit(int inheritsched)
{
	return pthread_attr_setinheritsched(&m_Impl.thread_attr, inheritsched);
}

int CThread::GetAttrInherit(int& inheritsched)
{
	return pthread_attr_getinheritsched(&m_Impl.thread_attr, &inheritsched);
}

int CThread::SetAttrSchedPolicy(int policy)
{
	return pthread_attr_setinheritsched(&m_Impl.thread_attr, policy);
}

int CThread::GetAttrSchedPolicy(int& policy)
{
	return pthread_attr_getinheritsched(&m_Impl.thread_attr, &policy);
}

int CThread::SetStack(void* stack, size_t stack_size)
{
	return pthread_attr_setstack(&m_Impl.thread_attr, stack, stack_size);
}

int CThread::GetStack(void** stack, size_t& stack_size)
{
	return pthread_attr_getstack(&m_Impl.thread_attr, stack, &stack_size);
}

int CThread::SetStackSize(size_t stack_size)
{
	return pthread_attr_setstacksize(&m_Impl.thread_attr, stack_size);
}

int CThread::GetStackSize(size_t& stack_size)
{
	return pthread_attr_getstacksize(&m_Impl.thread_attr, &stack_size);
}

bool CThread::operator==(const CThread &rhs)
{
	if ( pthread_equal(this->m_Impl.thread, rhs.m_Impl.thread) )
		return true;
	else
		return false;
}

int CThread::SendCanCel(const CThread& ThreadToCancel)
{
	return pthread_cancel(ThreadToCancel.m_Impl.thread);
}
