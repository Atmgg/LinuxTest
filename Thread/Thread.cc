#include <pthread.h>
#include <errno.h>
#include "Thread.h"
#include "Comm/Global.h"

using namespace std;
using namespace LinuxTest;

CThread::CThread()
{
}

CThread::~CThread()
{
}

int CThread::Creat( void *(*start_routine) (void *), void *arg, const pthread_attr_t *attr )
{
	if (!start_routine)
		return ERR_NULL_POINTER;

	int ret = pthread_create( &(m_Impl.thread), attr, start_routine, arg );
	if ( 0 != ret )
		return errno;

	return SUCCEED;
}
