#ifndef  CLTHREADPOOL_H
#define  CLTHREADPOOL_H

#include "CLFunctionProvider.h"
#include "CLThread.h"

#define  THREAD_MAX_NUX 16
class CLThreadPool
{
public:
	CLThreadPool( int ThreadsNum ,const char* strFuncProviderName );
	virtual ~CLThreadPool();

public:
	bool ThreadsRun( void* pContext );

private:
	int m_ThreadsNum;
	CLFunctionProvider* m_pFunctionProvider;
	CLThread* m_pThreads[THREAD_MAX_NUX];
};

#endif