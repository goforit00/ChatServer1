#include "CLMessageSerializer.h"
#include "CLMessage.h"
#include "CLMemManagerByMemPool.h"
//-------------------------------------------------------------------------------------
//CLMessageSerializer
CLMessageSerializer::CLMessageSerializer()
{
}

CLMessageSerializer::~CLMessageSerializer()
{
}

//-------------------------------------------------------------------------------------
//CLAddMsgSerializer
CLAddMsgSerializer::CLAddMsgSerializer()
{
}

CLAddMsgSerializer::~CLMessageSerializer()
{
}

char* CLMessageSerializer::Serialize( CLMessage* pMsg , unsigned int* pFullLength , unsigned int HeadLength )
{
	CLAddMessage* pAddMsg = (CLAddMessage*)pMsg;

	*pFullLength = HeadLength+sizeof(unsigned long)+ sizeof(int)+sizeof(int);
	char *pBuf = (char*)_Malloc(*pFullLength);

	*(unsigned int *)pBuf = HeadLength;

	long *pID = (unsigned long*)(pBuf+HeadLength);
	*pID = pAddMsg->m_clMsgID;

	int *pi =(int)(pBuf+HeadLength+sizeof(unsigned long));
	*pi = pAddMsg->m_adder1;

	int *pj = (int)(pBuf+HeadLength+sizeof(unsigned long) +sizeof(int));
	*pj = pAddMsg->m_adder2;

	return pBuf;
}


//----------------------------------------------------------------------------------------
CLAddResultMsgSerializer::CLAddResultMsgSerializer()
{
}

CLAddResultMsgSerializer::~CLAddResultMsgSerializer()
{
}

char* CLAddResultMsgSerializer::Serialize( CLMessage* pMsg , unsigned int* pFullLength , unsigned int HeadLength )
{
	CLAddResultMessage* pAddResMsg = (CLAddResultMessage*)pMsg;
	
	*pFullLength = HeadLength +sizeof(unsigned long ) +sizeof(int);
	char  *pBuf = (char*)_Malloc(*pFullLength);

	*(unsigned int*)pBuf = HeadLength;

	unsigned long *pID = (unsigned long*)(pBuf+sizeof(HeadLength));
	pAddResMsg->m_clMsgID;

	int *addres = (int*)(pBuf+sizeof(HeadLength)+sizeof(unsigned long));
	*addres = pAddResMsg->m_addresult;

	return pBuf;
}
