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

//�����ṩ�Ĺ����ӿ�
//�����ڴ�
void* _Malloc( int isize );
//�����ڴ�
void  _Free( void* addr );


#endif