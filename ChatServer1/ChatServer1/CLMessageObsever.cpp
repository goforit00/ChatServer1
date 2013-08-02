#include "CLMessageObsever.h"

CLMessageObsever::CLMessageObsever()
{
}

CLMessageObsever::~CLMessageObsever()
{
}

CLMessage* CLMessageObsever::On_AddMsg( CLMessage *pMsg )
{
	CLAddMessage* pAddMsg = (CLAddMessage*)pMsg;
	CLAddResultMessage* pAddResMsg = (CLAddResultMessage*)_Malloc( sizeof(CLAddResultMessage) );
	pAddResMsg->m_addresult = pAddMsg->m_adder1+pAddMsg->m_adder2;
	//进行日志记录    
	char buff[256];
	memset(buff , 0 , 256);
	sprintf_s(buff , 256,"%d+%d",pAddMsg->m_adder1,pAddMsg->m_adder2);
	WriteLogMsg( buff , LOG_ERROR , (void*)1 )
	
	_Free( pMsg );
	return pAddResMsg;
}