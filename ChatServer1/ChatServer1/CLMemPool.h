#ifndef  CLMEMPOOL_H
#define  CLMEMPOOL_H

#define  MEMPOOLSIZE   1024*1024*4  //默认大小4M
#include "CLMutex.h"

class CLMemPool
{
public:
	static CLMemPool* GetInstance();
public:
	void* GetMemory( int size );
	long GetMemoryStartAddr();
    long GetMemoryEndAddr();
private:
	CLMemPool();
	//	CLMemPool( int size );
	~CLMemPool();
private:
	static CLMemPool* m_Instance; 
	int m_iTotleSize;//总大小
	int m_iStart;//空闲空间开始处
	char* m_pMempool;//内存池实际空间

	//用于线程安全
	static CLMutex  m_Mutex_Instance;
	CLMutex  m_Mutex_GetMem;
};

//从内存池中得到内存块大小的  公共接口函数
void* GetMemFromMemPool( int size );

#endif
