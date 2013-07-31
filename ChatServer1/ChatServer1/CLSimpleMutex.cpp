#include "CLSimpleMutex.h"
CLSimpleMutex::CLSimpleMutex()
{
	m_pMutex = new pthread_mutex_t;
	if( m_pMutex == NULL )
		throw "In CLMutex::CLMutex() error";
	pthread_mutex_init( m_pMutex , 0 );
}

CLSimpleMutex::~CLSimpleMutex()
{
	pthread_mutex_destroy( m_pMutex );
	if( m_pMutex != NULL )
		delete m_pMutex;
}

bool CLSimpleMutex::Lock()
{
	if( pthread_mutex_lock( m_pMutex ) != 0 )
		return false;
	return true;
}

bool CLSimpleMutex::UnLock()
{
	if( pthread_mutex_unlock( m_pMutex ) != 0 )
		return false;
	return true;
}
