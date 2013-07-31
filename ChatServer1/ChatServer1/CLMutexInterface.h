#ifndef  CLMUTEXINTERFACE_H
#define  CLMUTEXINTERFACE_H

class CLMutexInterface
{
public:
	CLMutexInterface();
	virtual ~CLMutexInterface();

	virtual bool Initialize() = 0;
	virtual bool Uninitialize() = 0;

	virtual bool Lock() = 0;
	virtual bool UnLock() = 0;
};

#endif