#ifndef  CLMEMMANAGERBYMEMPOOL_H
#define  CLMEMMANAGERBYMEMPOOL_H
#include "CLMemManager.h"
#include "CLMutex.h"

#define  MEMCHUNKNUM  16//��8��128
#define  MEMBLOCKNUM  20//ÿ��chunk��20��block
#define  BLOCK_SIZE_MIN  8//��С�Ŀ��С
#define  BLOCK_SIZE_MAX   128
//��8��128�ֽ� ��16����δ����ǰ��ÿ����ǰ���ֽڱ�ʾnext �������ÿ����ǰ���ֽڱ�ʾ�ֽ���

typedef struct _STOBJ
{
	struct _STOBJ* next;
}ST_OBJ;

class CLMemManagerByMemPool : public CLMemManager
{
public:
	static  CLMemManagerByMemPool* GetInstance();

public:
	virtual void* Malloc( int isize );
	virtual void Free( void* addr );

private:
	CLMemManagerByMemPool();
	~CLMemManagerByMemPool();
private:
	bool Initial();
	int GetBlockSize( int isize );
private:
	ST_OBJ  m_obj[MEMCHUNKNUM];
	int m_iObjNum[MEMCHUNKNUM];
	static CLMemManagerByMemPool* m_instance;

private:
	static CLMutex  m_Mutex_Instance;
	CLMutex  m_Mutex_Mem;
};

void* _Malloc( int isize );
void  _Free( void* addr );

#endif