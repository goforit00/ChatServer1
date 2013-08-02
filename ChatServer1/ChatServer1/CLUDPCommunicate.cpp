#include "CLUDPCommunicate.h"

CLUDPCommunicate::CLUDPCommunicate()
{
	m_sock_fd = -1;
	memset( &m_MyAddr , 0 , sizeof(m_MyAddr) );
	memset( &m_ClientAddr , 0 , sizeof( m_ClientAddr ) );
	memset( &m_SendToAddr , 0 , sizeof( m_SendToAddr ) );
}

CLUDPCommunicate::CLUDPCommunicate( int fd )
{
	m_sock_fd = fd ;
}

CLUDPCommunicate::~CLUDPCommunicate()
{
}

bool CLUDPCommunicate::Initial()
{
	if( m_sock_fd < 0 )
		m_sock_fd = socket( AF_INET , SOCK_DGRAM , 0 );
	if( m_sock_fd <= 0 )
		return false;

	//ÉèÖÃµØÖ·
	m_MyAddr.sin_family = AF_INET;
	m_MyAddr.sin_port = htons( PORT );
	m_MyAddr.sin_addr.s_addr = htonl( INADDR_ANY );
	//bind
	int rbind = bind( m_sock_fd , (struct sockaddr*)& m_MyAddr , sizeof( m_MyAddr )) ;
	if( rbind < 0 )
	{
		cout<<"bind error"<<endl;
		return false;
	}
	return true;
}


int CLUDPCommunicate::Read(char* pBuf , int iBufLen )
{
	if( pBuf == NULL || iBufLen <=0 )
		return -1;

	socklen_t len = sizeof( m_ClientAddr );
	int n= recvfrom( m_sock_fd , pBuf , iBufLen , 0 , (struct sockaddr*)&m_ClientAddr , &len );
	if( n< 0 )
		return -1;
	return n;
}

bool CLUDPCommunicate::SetSendToAddr( struct sockaddr_in sendtoaddr )
{
	m_SendToAddr = sendtoaddr;
}

struct sockaddr_in CLUDPCommunicate::GetAddrFromRead()
{
	return m_ClientAddr;
}


int CLUDPCommunicate::Write(char* pBuf , int iBufLen )
{
	if( pBuf == NULL || strlen(pBuf)<= 0 || iBufLen <= 0 )
		return -1;
	int n = sendto( m_sock_fd , pBuf , iBufLen , 0  ,(struct sockaddr*)&m_SendToAddr , sizeof(m_SendToAddr) );
	if( n <= 0 )
		return -1;
	return n;
}
