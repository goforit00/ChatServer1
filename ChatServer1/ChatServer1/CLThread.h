#ifndef   CLTHREAD_H
#define  CLTHREAD_H

#include <pthread.h>
#include "CLFunctionProvider.h"

class CLThread
{
public:
	CLThread( CLFunctionProvider* pFunctionProvider , bool isWaitForDeath );
	virtual ~CLThread();

	bool Run( void* pContext );
	bool WaitForDeath();

private:
	static void* StartFuntionThread( void* pContext );

protected:
	pthread_t m_ThreadID;
	void* m_pContext;
	bool m_isWaitForDeath;

	CLFunctionProvider *m_pFuncProvider;
};


#endif
