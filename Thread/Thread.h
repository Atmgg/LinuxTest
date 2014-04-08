#ifndef _THREAD_H_
#define _THREAD_H_

namespace LinuxTest
{

typedef struct 
{
	pthread_t thread;
	
}CThreadImpl;

class CThread
{
	public:
		CThread();
		virtual ~CThread();
		int Creat( void *(*start_routine) (void *), void *arg, const pthread_attr_t *attr = NULL );
		int Join();
	private:
		CThread(const CThread &cms);
		const CThread& operator= (CThread &rhs);

		CThreadImpl m_Impl;
};

}

#endif
