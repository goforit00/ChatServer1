#include "CLMessageDeserializer.h"

CLMessageDeserializer::CLMessageDeserializer()
{
}

CLMessageDeserializer::~CLMessageDeserializer()
{
}

//--------------------------------------------------------------------------------------
CLAddMsgDeserializer::CLAddMsgDeserializer()
{
}

CLAddMsgDeserializer::~CLAddMsgDeserializer()
{
}

CLMessage* CLAddMsgDeserializer::Deserialize(char* pBuffer)
{
	if( pBuffer == NULL || strlen( pBuffer) == 0 )
		return NULL;

	unsigned long id= *(unsigned long*)(pBuffer);
	if( id != ADD_MESSAGE_ID )
		return NULL ;

	CLAddMessage* pAddMsg = (CLAddMessage*)_Malloc(sizeof(CLAddMessage));
	pAddMsg->m_adder1 = *(int*)(pBuffer + sizeof(unsigned long));
	pAddMsg->m_adder2 = *(int*)(pBuffer+sizeof(unsigned long)+sizeof(int));

	return pAddMsg;
}