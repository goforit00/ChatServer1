#include "CLChatServerMessageSend.h"

CLChatServerMessageSend::CLChatServerMessageSend( CLMessageQueue* pSendMsgQueue )
{
	if( pSendMsgQueue == NULL )
		throw "pSendMsgQueue is NULL";
	m_pSendMsgQueue = pSendMsgQueue;
}

CLChatServerMessageSend::~CLChatServerMessageSend()
{
	//把map中的删除
}

bool CLChatServerMessageSend::Initialize()
{
	Register( ADD_RESULT_MESSAGE_ID , new CLAddResultMsgSerializer() );
	return true;
}

bool CLChatServerMessageSend::Register( unsigned long id , CLMessageSerializer* MsgSer )
{
	std::map<unsigned long , CLMessageSerializer*>::iterator it;
	it = m_MsgID_MsgSer_MapTable.find( id );
	if( it != m_MsgID_MsgSer_MapTable.end() )
		return false;
	m_MsgID_MsgSer_MapTable[id] = MsgSer;
	return true;
}

bool CLChatServerMessageSend::FuntionProviderRun(void* pContext)
{
	if ( false == Initialize() )
		return false;
	while( true )
	{
	//从队列中取出消息，此处不进行发送，而进行日志记录
	//先进行序列化
		char  *buff ;
		CLMessage* pMsg = m_pSendMsgQueue->GetMessage();
		unsigned long id = pMsg->m_clMsgID;
		std::map<unsigned long , CLMessageSerializer*>::iterator it;
		it = m_MsgID_MsgSer_MapTable.find(id);

		int bufflen;
		if( it != m_MsgID_MsgSer_MapTable.end() )
			buff = it->second->Serialize(pMsg ,&bufflen,sizeof(int) );

		//写入日志
		WriteLogMsg( buff , LOG_ERROR , (void*)0 );
	}


	return true;
}
