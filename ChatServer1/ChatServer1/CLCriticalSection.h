#ifndef  CLCRITICALSECTION_H
#define CLCRITICALSECTION_H

class CLMutex;
class CLCriticalSection
{
public:
     CLCriticalSection( CLMutex *pMutex );
	  virtual ~CLCriticalSection();

private:
     CLCriticalSection(const CLCriticalSection&);
	 CLCriticalSection& operator=( const CLCriticalSection& );

private:
	CLMutex *m_pMutex;
};

#endif