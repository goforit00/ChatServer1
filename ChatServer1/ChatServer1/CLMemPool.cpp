#include "CLMemPool.h"
#include "CLCriticalSection.h"
#include <iostream>
CLMemPool* CLMemPool::m_Instance = NULL;
CLMutex CLMemPool::m_Mutex_Instance = CLMutex();

CLMemPool* CLMemPool::GetInstance()
{
	if( m_Instance == NULL )
	{
		//加锁
		{
			CLCriticalSection cs(&m_Mutex_Instance);
			if( m_Instance != NULL )
			{
				return m_Instance;
			}
			m_Instance = new CLMemPool();
		//此处进行解锁
		}
		return m_Instance;
	}
	else 
		return m_Instance;
}


CLMemPool::CLMemPool()
{
	m_pMempool = new char[MEMPOOLSIZE];
	if( m_pMempool == NULL )
		throw "MemPool fail\n";
    m_iTotleSize=MEMPOOLSIZE;
	m_iStart = 0;
}
/*
CLMemPool::CLMemPool( int isize )
{
	m_pMempool = new char[ isize ];
	if( m_pMempool == NULL )
	    throw "MemPool fail\n";
	m_iTotleSize = MEMPOOLSIZE;
	m_iStart = 0;
}*/

CLMemPool::~CLMemPool()
{
	if( m_pMempool != NULL )
		delete [] m_pMempool;
}

void* CLMemPool::GetMemory( int size )
{//加锁
	CLCriticalSection cs(&m_Mutex_GetMem);

	int iret=0;
	if( size <= 0 )
		return NULL;
    if( m_iTotleSize - m_iStart < size )
		return NULL;
	else 
	{
		iret = m_iStart;
		m_iStart+=size;
	}
	return (void*)(m_pMempool+iret);
	//解锁
}

long CLMemPool::GetMemoryStartAddr()
{
	return (long)(void*)m_pMempool;
}

long CLMemPool::GetMemoryEndAddr()
{
	return (long)(void*)(m_pMempool+m_iTotleSize);
}

void* GetMemFromMemPool( int size )
{
    static CLMemPool  *MemPool = CLMemPool::GetInstance();
	return MemPool->GetMemory( size );
}
