#include "CLChatServerMessageSend.h"

CLChatServerMessageSend::CLChatServerMessageSend( CLMessageQueue* pSendMsgQueue )
{
	if( pSendMsgQueue == NULL )
		throw "pSendMsgQueue is NULL";
	m_pSendMsgQueue = pSendMsgQueue;
}

CLChatServerMessageSend::~CLChatServerMessageSend()
{
	//��map�е�ɾ��
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
	//�Ӷ�����ȡ����Ϣ���˴������з��ͣ���������־��¼
	//�Ƚ������л�
		char  *buff ;
		CLMessage* pMsg = m_pSendMsgQueue->GetMessage();
		unsigned long id = pMsg->m_clMsgID;
		std::map<unsigned long , CLMessageSerializer*>::iterator it;
		it = m_MsgID_MsgSer_MapTable.find(id);

		int bufflen;
		if( it != m_MsgID_MsgSer_MapTable.end() )
			buff = it->second->Serialize(pMsg ,&bufflen,sizeof(int) );

		//д����־
		WriteLogMsg( buff , LOG_ERROR , (void*)0 );
	}


	return true;
}
