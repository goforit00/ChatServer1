#include "CLMutexByRecordLockingAndPThread.h"

CLMutexByRecordLockingAndPThread::CLMutexByRecordLockingAndPThread( const char* pstrFileName )
:m_ProcessMutex( pstrFileName , MUTEX_USE_RECORD_LOCK )
{

}

CLMutexByRecordLockingAndPThread::CLMutexByRecordLockingAndPThread( const char* pstrFileName , pthread_mutex_t* pMutex )
:m_ThreadMutex(pMutex ),m_ProcessMutex(pstrFileName,MUTEX_USE_RECORD_LOCK)
{

}

CLMutexByRecordLockingAndPThread::~CLMutexByRecordLockingAndPThread()
{

}


bool CLMutexByRecordLockingAndPThread::Lock()
{
	if( m_ThreadMutex.Lock() == false )
		return false;
	
	return m_ProcessMutex.Lock();
}

bool CLMutexByRecordLockingAndPThread::UnLock()
{
	if( m_ProcessMutex.UnLock() == false )
		return false;
	return m_ThreadMutex.UnLock();
}

bool CLMutexByRecordLockingAndPThread::Initialize()
{
	return true;
}

bool CLMutexByRecordLockingAndPThread::Uninitialize()
{
	return true;
}
