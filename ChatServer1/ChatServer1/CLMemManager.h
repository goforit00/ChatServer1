#ifndef  CLMEMMANAGER_H
#define  CLMEMMANAGER_H

class  CLMemManager
{
public:
	CLMemManager();
	virtual ~CLMemManager();
public:
	virtual void* Malloc( int isize ) = 0;
	virtual void Free( void* addr ) = 0;
};

//对外提供的公共接口
//分配内存
void* _Malloc( int isize );
//回收内存
void  _Free( void* addr );


#endif