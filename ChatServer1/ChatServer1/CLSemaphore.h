#ifndef  CLSEMAPHORE_H
#define  CLSEMAPHORE_H
#include <semaphore.h>
class CLSemaphore
{
public: 
	CLSemaphore( int SemStartNum );
	~CLSemaphore();

public:
	bool P();
	bool V();

private:
	sem_t  *m_pSem;
};


#endif