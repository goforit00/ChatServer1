#ifndef  CLUDPCOMMUNICATE_H
#define  CLUDPCOMMUNICATE_H

#include "CLCommunicate.h"
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
#include <unistd.h>
using namespace std;

#define  PORT   8989
#define  IP   "127.0.0.1"

class  CLUDPCommunicate : public CLCommunicate
{
public:
	CLUDPCommunicate();
	CLUDPCommunicate( int fd );
	virtual ~CLUDPCommunicate();
public:
	virtual bool Initial();
	virtual int Read(char* pBuf , int iBufLen );
	virtual int Write(char* pBuf , int iBufLen );

	struct sockaddr_in GetAddrFromRead();
	bool SetSendToAddr( struct sockaddr_in sendtoaddr );

private:
	int  m_sock_fd;
	struct sockaddr_in  m_MyAddr;
	struct sockaddr_in  m_ClientAddr;//这是recvfrom时得到的客户端的地址
	struct sockaddr_in  m_SendToAddr;//这是sendto时的地址
};

#endif