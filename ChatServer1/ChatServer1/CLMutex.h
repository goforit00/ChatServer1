#ifndef   CLMUTEX_H
#define   CLMUTEX_H

#include<pthread.h>

#include "CLMutexInterface.h"
//#include "CLMutexByPThread.h"
//#include "CLMutexByRecordLocking.h"
//#include "CLMutexByRecordLockingAndPThread.h"

#define  MUTEX_USE_RECORD_LOCK  1
#define  MUTEX_USE_RECORD_LOCK_AND_PTHREAD 2

//extern pthread_mutex_t;

class CLMutex
{
public:
	CLMutex();
	explicit CLMutex( pthread_mutex_t* pMutex );
	CLMutex( const char* pstrFileName , int nType );
	CLMutex( const char* pstrFileName , pthread_mutex_t* pMutex );
	virtual ~CLMutex();

	bool Lock();
	bool UnLock();

	CLMutexInterface* GetMutexInterface();
private:
	CLMutexInterface* m_pMutex;
};

#endif
