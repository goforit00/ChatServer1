#include "CLMutexByPThread.h"

CLMutexByPThread::CLMutexByPThread()
{
	m_pMutex = new pthread_mutex_t;
	m_bNeededDestroy = true ;
	
	int r = pthread_mutex_init( m_pMutex , 0 );
	if( r != 0 )
		throw "In CLMutexByPThread::CLMutexByPThread() , pthread_mutex_init() error";
}

CLMutexByPThread::CLMutexByPThread( pthread_mutex_t* pMutex )
{
	if( pMutex == NULL )
		throw "pMutex is NULL";
	m_pMutex = pMutex;
	m_bNeededDestroy = false ;
}

CLMutexByPThread::~CLMutexByPThread()
{
	if( m_bNeededDestroy == true )
	{
		int r = pthread_mutex_destroy( m_pMutex );
		if( r != 0 )
			throw "In CLMutexByPThread::~CLMutexByPThread(),pthread_mutex_destroy() error";
		delete m_pMutex;
	}
}

bool CLMutexByPThread::Initialize()
{
    return true;
}

bool CLMutexByPThread::Uninitialize()
{
	return true;
}

bool CLMutexByPThread::Lock()
{
	if( 0 == pthread_mutex_lock( m_pMutex ) )
		return true;
	else 
		return false;
}

bool CLMutexByPThread::UnLock()
{
	 if( 0 == pthread_mutex_unlock( m_pMutex) )
		 return true;
	 else 
		 return false;
}

pthread_mutex_t* CLMutexByPThread::GetMutexPointer()
{
	return m_pMutex;
}