#include "CLMutex.h"
#include "CLMutexByPThread.h"
#include "CLMutexByRecordLocking.h"
#include "CLMutexByRecordLockingAndPThread.h"

CLMutex::CLMutex()
{
	m_pMutex = new CLMutexByPThread();
    
	if( m_pMutex->Initialize() == false )
	{
		throw "CLMutexByPThread::Initialize() error";
		delete m_pMutex;
	}

}

CLMutex::CLMutex( pthread_mutex_t* pMutex )
{
	m_pMutex = new CLMutexByPThread( pMutex );
	if( m_pMutex->Initialize() == false )
	{
		delete m_pMutex;
		throw "CLMutexByPThread::Initialize() error";
	}
}

CLMutex::CLMutex( const char* pstrFileName , int nType )
{
	if( nType == MUTEX_USE_RECORD_LOCK )
	{
		m_pMutex = new CLMutexByRecordLocking( pstrFileName );
	}
	else if( nType == MUTEX_USE_RECORD_LOCK_AND_PTHREAD )
	{
		m_pMutex = new CLMutexByRecordLockingAndPThread( pstrFileName );
	}

	if( m_pMutex->Initialize() == false )
	{
		delete m_pMutex;
		throw "In CLMutex::CLMutex() ,Initialize() error";
	}
		
}

CLMutex::CLMutex( const char* pstrFileName , pthread_mutex_t* pMutex )
{
	m_pMutex = new CLMutexByRecordLockingAndPThread( pstrFileName , pMutex );
	if( m_pMutex->Initialize() == false )
	{
		delete m_pMutex;
		throw "CLMutexByRecordLockingAndPThread::Initialize() error";
	}
}

CLMutex::~CLMutex()
{
	if( m_pMutex->Uninitialize() == false )
		throw "Uninitialize() error";
	delete m_pMutex;
}

bool CLMutex::Lock()
{
	return m_pMutex->Lock();
}

bool CLMutex::UnLock()
{
	return m_pMutex->UnLock();
}

CLMutexInterface* CLMutex::GetMutexInterface()
{
	return m_pMutex;
}
