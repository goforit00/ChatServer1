#include "CLCriticalSection.h"
#include "CLMutex.h"

CLCriticalSection::CLCriticalSection( CLMutex *pMutex )
{
	if( pMutex == NULL )
		throw "In CLCriticalSection::CLCriticalSection(), pMutex == NULL";

	m_pMutex = pMutex;

	if( m_pMutex->Lock() == false )
		throw "In CLCriticalSection::CLCriticalSection(), m_pMutex->Lock error";
}

CLCriticalSection::~CLCriticalSection()
{
      if( m_pMutex->UnLock() == false )
		  throw "In CLCriticalSection::CLCriticalSection(), m_pMutex->UnLock error";
}
