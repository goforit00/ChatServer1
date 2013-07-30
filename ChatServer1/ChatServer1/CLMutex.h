#ifndef  CLMUTEX_H
#define  CLMUTEX_H
#include<pthread.h>

class CLMutex
{
public:
	CLMutex();
	~CLMutex();

	bool Lock();
	bool UnLock();

private:
	pthread_mutex_t *m_pMutex;
};

#endif