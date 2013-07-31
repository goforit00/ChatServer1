#ifndef  CLMUTEXBYRECORDLOCKING_H
#define  CLMUTEXBYRECORDLOCKING_H

#define  FILE_PATH_FOR_RECORD_LOCKING "File_RecordLocking.txt"
#include "CLMutexInterface.h"
#include <string>
using namespace  std;

class CLMutexByRecordLocking :public CLMutexInterface
{
public:
	CLMutexByRecordLocking( const char* pstrFileName );
	virtual ~CLMutexByRecordLocking();

	virtual bool Initialize();
	virtual bool Uninitialize();

	virtual bool Lock();
	virtual bool UnLock();

private:
	int m_Fd;
	string m_strFileName;
};

#endif