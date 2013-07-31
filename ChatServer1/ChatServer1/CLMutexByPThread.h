#ifndef  CLMUTEXBYPTHREAD_H
#define CLMUTEXBYPTHREAD_H

#include <pthread.h>
#include "CLMutexInterface.h"

class  CLMutexByPThread : public CLMutexInterface
{
public:
	CLMutexByPThread();
	CLMutexByPThread( pthread_mutex_t* pMutex );
	virtual ~CLMutexByPThread();

	virtual bool Initialize();
	virtual bool Uninitialize();

	virtual bool Lock();
	virtual bool UnLock();

	pthread_mutex_t* GetMutexPointer();

private:
	pthread_mutex_t* m_pMutex;
	bool m_bNeededDestroy;
};

#endif