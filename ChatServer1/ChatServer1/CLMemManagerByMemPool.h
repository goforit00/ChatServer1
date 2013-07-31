#ifndef  CLMEMMANAGERBYMEMPOOL_H
#define  CLMEMMANAGERBYMEMPOOL_H
#include "CLMemManager.h"
#include "CLMutex.h"

#define  MEMCHUNKNUM  16//从8到128
#define  MEMBLOCKNUM  20//每个chunk有20个block
#define  BLOCK_SIZE_MIN  8//最小的块大小
#define  BLOCK_SIZE_MAX   128
//从8到128字节 共16个，未分配前，每个的前四字节表示next ，分配后，每个的前四字节表示字节数

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