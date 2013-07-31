#ifndef  CLSIMPLEMUTEX_H
#define  CLSIMPLEMUTEX_H
#include<pthread.h>


class CLSimpleMutex
{
public:
	CLSimpleMutex();
	~CLSimpleMutex();

	bool Lock();
	bool UnLock();

private:
	pthread_mutex_t *m_pMutex;
};

#endif