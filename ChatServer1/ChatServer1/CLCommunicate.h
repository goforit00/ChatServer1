#ifndef  CLCOMMUNICATE_H
#define  CLCOMMUNICATE_H

class CLCommunicate
{
public:
	CLCommunicate();
	virtual ~CLCommunicate();

public:
	virtual bool Initial() = 0;
	virtual int Read(char* pBuf , int iBufLen ) = 0 ;
	virtual int Write(char* pBuf , int iBufLen ) = 0 ;

};

#endif