#include "CLLogger.h"
#include "CLDate.h"
#include "CLCriticalSection.h"
#include "CLMutexByPThread.h"
#include "CLMutexByRecordLocking.h"
#include "CLMutexByRecordLockingAndPThread.h"
#include "CLMutexInterface.h"
#include <iostream>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
using namespace std;

CLLogger* CLLogger::m_Instance = NULL;
CLMutex  CLLogger::m_Mutex_Instance = CLMutex();

CLLogger::CLLogger()
{
	m_Fd = open( LOG_FILE_NAME , O_RDWR|O_CREAT |O_APPEND , S_IRUSR|S_IWUSR );
	if( m_Fd == -1 )
		throw "In CLLogger::CLLogger(), open error";

	m_pLogBuffer = new char[ BUFFER_SIZE_LOG_FILE ];
	m_nUsedBytesForBuffer = 0;

	m_DateTime = CLDate::GetInstance();
	m_Mutex_Write = CLMutex(LOG_FILE_NAME,MUTEX_USE_RECORD_LOCK_AND_PTHREAD);
}

CLLogger::~CLLogger()
{
	delete [] m_pLogBuffer;

	close( m_Fd );
}


CLLogger* CLLogger::GetInstance()
{
	if( m_Instance == NULL )
	{
		CLCriticalSection cs(&m_Mutex_Instance);
        if( m_Instance != NULL )
			return m_Instance;
		m_Instance = new CLLogger();
	}
	return m_Instance;
}

bool CLLogger::WriteLogMsg(const char* pMsg , LOG_TYPE logtype ,void* exData )
{
	if( pMsg == NULL || strlen(pMsg) == 0 )
		return false;

	char buf[MAX_SIZE];

	//根据logtype进行写不同的内容，此处只记录Log_Error
	if( logtype == LOG_ERROR)
	{
		long errcode = (long)exData;//*((long*)exData); 
		snprintf( buf ,MAX_SIZE , "	Error code :%ld\r\n",errcode);
	}

	int len_msg = strlen( pMsg );
	int len_code = strlen( buf );
	unsigned int total_len = len_msg+ len_code;
	char DateBuf[DATEBUF_SIZE];
	int len_date = m_DateTime->GetDate(DateBuf,DATEBUF_SIZE);

	//进行写入
	if( m_Instance == NULL )
		return false;
	if( total_len > BUFFER_SIZE_LOG_FILE )
	{
		CLCriticalSection cs(&m_Mutex_Write);
		int r = write(m_Fd , DateBuf , len_date);
		if( r <= 0 )
			return false;
		r = write( m_Fd , pMsg , len_msg );
		if( r <= 0 )
			return false ;
		r = write( m_Fd , buf , len_code );
		if( r <= 0 )
			return false;

		return true;
	}

	unsigned int nLeftroom = BUFFER_SIZE_LOG_FILE - m_nUsedBytesForBuffer;
	CLCriticalSection cs(&m_Mutex_Write);
	if( total_len > nLeftroom )
	{
		int r= write( m_Fd , m_pLogBuffer , m_nUsedBytesForBuffer );
		if( r <= 0 )
			return false;
		m_nUsedBytesForBuffer = 0;
	}

	memcpy( m_pLogBuffer + m_nUsedBytesForBuffer , DateBuf , len_date );
	m_nUsedBytesForBuffer += len_date;

	memcpy( m_pLogBuffer + m_nUsedBytesForBuffer , pMsg , len_msg );
	m_nUsedBytesForBuffer += len_msg;

	memcpy( m_pLogBuffer + m_nUsedBytesForBuffer , buf , len_code );
	m_nUsedBytesForBuffer += len_code;

	return true;
}

bool CLLogger::WriteLogDirector(const char* pMsg , LOG_TYPE logtype , void* exData )
{
	if( pMsg == NULL || strlen(pMsg) == 0 )
		return false;
	if( m_Fd == -1 )
		return false;

	char buf[MAX_SIZE];

	if( logtype == LOG_ERROR )
	{
		long errcode = (long)exData;
		snprintf( buf , MAX_SIZE , "	Error code:%ld\r\n" , errcode );
	}
	char Datebuf[DATEBUF_SIZE];
	int len_date = m_DateTime->GetDate(Datebuf , DATEBUF_SIZE);

	CLCriticalSection cs(&m_Mutex_Write);
	int r =write( m_Fd , Datebuf , len_date );
	if( r <= 0 )
		return false;
	r=write( m_Fd , pMsg , strlen( pMsg) );
	if( r <= 0 )
		return false;
	r = write( m_Fd , buf , strlen( buf ) );
	if( r <= 0 )
		return false;

	return true;
}

bool CLLogger::Flush()
{
	if( m_Instance == NULL )
		return false;

	CLCriticalSection cs(&m_Mutex_Write);
	if( m_nUsedBytesForBuffer == 0 )
		return true;

	int r = write( m_Fd , m_pLogBuffer , m_nUsedBytesForBuffer );
	if( r <= 0 )
		return false;
	return true;
}


bool WriteLogMsg( const char* pMsg , LOG_TYPE logtype , void* exData )
{
	CLLogger* pLogger = CLLogger::GetInstance();
	return pLogger->WriteLogMsg( pMsg , logtype , exData );
}

bool WriteLogDirector(const char* pMsg , LOG_TYPE logtype , void* exData )
{
	CLLogger* pLogger = CLLogger::GetInstance();
	return pLogger->WriteLogDirector( pMsg , logtype , exData );
}

bool LogFlush()
{
	CLLogger* pLogger = CLLogger::GetInstance();
	return pLogger->Flush();
}