#include "CLMutexByRecordLocking.h"
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <string>
#include <unistd.h>

CLMutexByRecordLocking::CLMutexByRecordLocking( const char* pstrFileName )
{
	if( ( pstrFileName == NULL ) || ( strlen(pstrFileName) == 0 ) )
		throw "In CLMutexByRecordLocking::CLMutexByRecordLocking(), pstrFileName error";
	m_strFileName = pstrFileName;
	m_Fd = open( m_strFileName.c_str() , O_RDWR|O_CREAT , S_IRUSR|S_IWUSR );
	if( m_Fd <= 0 )
		throw "In CLMutexByRecordLocking::CLMutexByRecordLocking , open() error";
}

CLMutexByRecordLocking::~CLMutexByRecordLocking()
{
	if( close(m_Fd) == -1 )
		throw "In CLMutexByRecordLocking::~CLMutexInterface , close() error ";
}

bool CLMutexByRecordLocking::Initialize()
{
	return true;
}

bool CLMutexByRecordLocking::Uninitialize()
{
	return true;
}

bool CLMutexByRecordLocking::Lock()
{
	m_Fd = open( m_strFileName.c_str() , O_RDWR | O_CREAT, S_IRUSR |S_IWUSR );
	if( m_Fd == -1 )
		return false;

	struct flock lock;
	lock.l_type = F_WRLCK;
	lock.l_start = 0;
	lock.l_whence = SEEK_SET;
	lock.l_len = 0;

	if( fcntl( m_Fd , F_SETLKW , &lock) == -1 )
		return false;

	return true;
}

bool CLMutexByRecordLocking::UnLock()
{
	struct flock lock;
	lock.l_type = F_UNLCK;
	lock.l_start = 0;
	lock.l_whence = SEEK_SET;
	lock.l_len = 0;

	if( fcntl(m_Fd , F_SETLKW , &lock ) == -1 )
		return false;
	return true;
}