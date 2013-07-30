#include "CLThreadPool.h"
#include "CLFuncProviderNameServer.h"
#include<iostream>
using namespace std;


CLThreadPool::CLThreadPool( int ThreadsNum ,const char* strFuncProviderName )
{
	if( ThreadsNum > THREAD_MAX_NUX )
		m_ThreadsNum = THREAD_MAX_NUX;
	m_ThreadsNum = ThreadsNum;
	CLFuncProviderNameServer *pfpns = CLFuncProviderNameServer::GetInstance();
	if( pfpns == NULL )
		cout<<"error"<<endl;
	m_pFunctionProvider =  pfpns->GetFunctionProvider(strFuncProviderName);
}

CLThreadPool::~CLThreadPool()
{
	//สอทลืสิด
	for( int i = 0 ;i <m_ThreadsNum; i ++ )
	{
		delete [] m_pThreads[i];
	}
}

bool CLThreadPool::ThreadsRun( void* pContext )
{
	if( m_pFunctionProvider == NULL )
		return false;
	for (int i = 0 ; i < m_ThreadsNum ; i++ )
	{
		m_pThreads[i] = new CLThread(m_pFunctionProvider , false );
		m_pThreads[i]->Run(pContext);
	}
	return true;
}
