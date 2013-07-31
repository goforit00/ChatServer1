#include "CLMemManagerByMemPool.h"
#include "CLMemPool.h"
#include "CLCriticalSection.h"
#include "CLMutex.h"
#include <iostream>
#include <stdlib.h>

CLMemManagerByMemPool* CLMemManagerByMemPool::m_instance = NULL;
CLMutex CLMemManagerByMemPool::m_Mutex_Instance = CLMutex();

CLMemManagerByMemPool::CLMemManagerByMemPool()
: CLMemManager()
{
	if( Initial() == false )
		throw "CLMemManagerByMemPool Fail\n";
}

CLMemManagerByMemPool::~CLMemManagerByMemPool()
{
}

CLMemManagerByMemPool* CLMemManagerByMemPool::GetInstance()
{
	if( m_instance == NULL )
	{
		{
			CLCriticalSection cs(&m_Mutex_Instance);
			if( m_instance != NULL )
				return m_instance;

			m_instance = new CLMemManagerByMemPool();
			return m_instance;
		}
	}
	else
		return m_instance;
}

//������һ�����͸�����chunk�����㹻��block
bool CLMemManagerByMemPool::Initial()
{
	for ( int i = 0 ; i < MEMCHUNKNUM ; i++ )
	{
		ST_OBJ *tmpobj = &m_obj[i] ;
		for ( int j = 0 ; j < MEMBLOCKNUM ; j++ )
		{
			tmpobj->next=(ST_OBJ*)GetMemFromMemPool( (i+1)*BLOCK_SIZE_MIN );
			if( tmpobj->next == NULL )
				return false;
			tmpobj = tmpobj->next;
		}
		tmpobj->next = NULL;
		m_iObjNum[i]=MEMBLOCKNUM;
	}

	return true;
}

//��������ռ���ʵĴ�Сblock��С
int  CLMemManagerByMemPool::GetBlockSize( int isize )
{
	if( isize <= 0 )
		return 0;

	return ( (isize+BLOCK_SIZE_MIN-1)&~(BLOCK_SIZE_MIN-1));
}


void* CLMemManagerByMemPool::Malloc( int isize )
{
	//�����������Ĵ�С ����ֱ�ӷ���
	if( isize > BLOCK_SIZE_MAX )
		return malloc(isize);

	int  corSize = GetBlockSize(isize+sizeof(char*));
	if( corSize <= 0 )
		return NULL;
	int index = corSize/BLOCK_SIZE_MIN - 1;
	ST_OBJ* retObj = &m_obj[index];

	//�����ڴ�
	CLCriticalSection cs(&m_Mutex_Mem);//����
	if( m_iObjNum[index] >0 )
	{
		retObj=retObj->next;
		m_obj[index].next=retObj->next;
		*(int*)retObj = isize;
		m_iObjNum[index]--;

		return (void*)((char*)(retObj)+sizeof(int));
	}
	else if( m_iObjNum[index] == 0 )
	{
		//û���ڴ棬���ڴ�ػ��
		ST_OBJ* tmpobj = (ST_OBJ*)GetMemFromMemPool(corSize);
		if( tmpobj == NULL )
			return NULL;
		*(int*)(tmpobj)=isize;
		return (void*)((char*)(tmpobj)+sizeof(int));
	}
	return NULL;
}

void CLMemManagerByMemPool::Free( void* addr )
{
	if( addr == NULL)
		return ;

	//�ȼ���Ƿ���ֱ�ӷ�����ڴ棬�����Ǵ��ڴ���з���ġ�
	static CLMemPool* ptmp = CLMemPool::GetInstance();
	if( ( (long)addr >= ptmp->GetMemoryEndAddr() ) || ( (long)addr <= ptmp->GetMemoryStartAddr() ) )
	{
		free(addr);
		return;
	}

	int isize = *(int*)((char*)addr-sizeof(int));
	int corsize = GetBlockSize(isize+sizeof(char*));

	int index = corsize/BLOCK_SIZE_MIN -1;

	ST_OBJ* tmpobj = &m_obj[index];
	tmpobj = tmpobj->next;

	CLCriticalSection  cs(&m_Mutex_Mem);//����
	m_obj[index].next = (ST_OBJ*)((char*)addr-sizeof(int));
	m_obj[index].next->next=tmpobj;
	m_iObjNum[index]++;

	return ;
}

void* _Malloc( int isize )
{
	static CLMemManager *MemManager = CLMemManagerByMemPool::GetInstance();
	return	MemManager->Malloc(isize);
}

void  _Free( void* addr )
{
	static  CLMemManager* MemManager = CLMemManagerByMemPool::GetInstance();
	MemManager->Free(addr);
}
