#ifndef  CLLOGGER_H
#define  CLLOGGER_H

#include "CLMutex.h"

enum  LOG_TYPE{LOG_ERROR,LOG_INFO};

#define  LOG_FILE_NAME  "logger"
#define  MAX_SIZE  256
#define  BUFFER_SIZE_LOG_FILE  4096
#define  DATEBUF_SIZE  32

class CLDate;
class  CLLogger
{
public:
	static CLLogger* GetInstance();
	bool WriteLogMsg( const char* pMsg , LOG_TYPE logtype , void* exData );//先写入缓冲
	bool WriteLogDirector(const char* pMsg , LOG_TYPE logtype , void* exData );//不写入缓冲
	bool Flush();
private:
	CLLogger();
	~CLLogger();
private:
	CLLogger( const CLLogger& );
	CLLogger& operator=( const CLLogger& );

private:
	static CLLogger* m_Instance;

	CLDate* m_DateTime;
private:
	int m_Fd;
	char* m_pLogBuffer;
	unsigned int m_nUsedBytesForBuffer;

private:
	static CLMutex  m_Mutex_Instance;
	CLMutex m_Mutex_Write;
};

bool WriteLogMsg( const char* pMsg , LOG_TYPE logtype , void* exData );
bool WriteLogDirector(const char* pMsg , LOG_TYPE logtype , void* exData );
bool LogFlush();


#endif
