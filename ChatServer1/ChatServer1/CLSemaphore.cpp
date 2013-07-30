#include "CLSemaphore.h"
#include <iostream>

CLSemaphore::CLSemaphore( int SemStartNum )
{
	m_pSem = new sem_t;
	if( m_pSem == NULL )
		throw "In CLSemaphone::CLSemaphone() error";
	if( sem_init( m_pSem , 0 , SemStartNum ) != 0 )
		throw "sem_init() error";
}

CLSemaphore::~CLSemaphore()
{
	sem_destroy( m_pSem );
	if( m_pSem != NULL )
		delete m_pSem;
}

bool CLSemaphore::P()
{
	if( sem_wait( m_pSem) != 0 )
		return false ;
	return true;
}

bool CLSemaphore::V()
{
	if( sem_post( m_pSem) != 0 )
		return false ;
	return true;
}
