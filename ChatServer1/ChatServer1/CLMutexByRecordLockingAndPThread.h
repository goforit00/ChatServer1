#ifndef  CLMUTEXBYRECORDLOCKINGANDPTHREAD_H
#define  CLMUTEXBYRECORDLOCKINGANDPTHREAD_H

#include <pthread.h>
#include "CLMutexInterface.h"
#include "CLMutex.h"

class CLMutexByRecordLockingAndPThread : public CLMutexInterface
{
public: 
	CLMutexByRecordLockingAndPThread( const char* pstrFileName );
	CLMutexByRecordLockingAndPThread( const char* pstrFileName , pthread_mutex_t* pMutex );

	virtual ~CLMutexByRecordLockingAndPThread();

	virtual bool Initialize();
	virtual bool Uninitialize();
	virtual bool Lock();
	virtual bool UnLock();
	
private:
	CLMutex  m_ThreadMutex;
	CLMutex  m_ProcessMutex;

};
#endif