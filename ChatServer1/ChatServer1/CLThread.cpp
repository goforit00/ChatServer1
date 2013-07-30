#include "CLThread.h"
#include <iostream>
using namespace std;
CLThread::CLThread( CLFunctionProvider* pFunctionProvider , bool isWaitForDeath )
{
	m_pFuncProvider = pFunctionProvider;
	m_isWaitForDeath = isWaitForDeath;
}

CLThread::~CLThread()
{
}

bool CLThread::Run( void* pContext )
{
	if( 0 == pthread_create( &m_ThreadID , 0 , StartFuntionThread , this ) )
	{
		m_pContext = pContext;
		return true;
	}
	return false;
}

void* CLThread::StartFuntionThread( void* pContext )
{
	CLThread* pthis = (CLThread*)pContext;
	if( pthis->m_isWaitForDeath == false )
	{ 
		int r = pthread_detach( pthread_self() );
		if( r != 0 )  	
			cout<<"pthread_detach error"<<endl;
	}	
	pthis->m_pFuncProvider->FuntionProviderRun( pthis->m_pContext );

}

bool CLThread::WaitForDeath()
{
	int r = pthread_join( m_ThreadID , 0 );
	if( r != 0 )
		return false;
	return true;
}
