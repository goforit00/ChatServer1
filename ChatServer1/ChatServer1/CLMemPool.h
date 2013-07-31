#ifndef  CLMEMPOOL_H
#define  CLMEMPOOL_H

#define  MEMPOOLSIZE   1024*1024*4  //Ĭ�ϴ�С4M
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
	int m_iTotleSize;//�ܴ�С
	int m_iStart;//���пռ俪ʼ��
	char* m_pMempool;//�ڴ��ʵ�ʿռ�

	//�����̰߳�ȫ
	static CLMutex  m_Mutex_Instance;
	CLMutex  m_Mutex_GetMem;
};

//���ڴ���еõ��ڴ���С��  �����ӿں���
void* GetMemFromMemPool( int size );

#endif
