#include "CLChatServerReceiveMessage.h"
#include "CLMessageQueue.h"
#include "CLMessageDeserializer.h"

#define   BUFF_SIZE  256

CLChatServerReceiveMessage::CLChatServerReceiveMessage(CLMessageQueue* pDealMsgQueue)
{
	m_pDealMsgQueue = pDealMsgQueue;
}

CLChatServerReceiveMessage::~CLChatServerReceiveMessage()
{
	//释放掉map中的内存
}

bool CLChatServerReceiveMessage::Initialize()
{
	if ( false == Register( ADD_MESSAGE_ID  , new CLAddMsgDeserializer() ) )
		return false;
    return true;
}

bool CLChatServerReceiveMessage::Register( unsigned long id , CLMessageDeserializer *pMsgDes )
{
	std::map<unsigned long ,CLMessageDeserializer>::iterator it;
	it = m_MsgID_MsgDeser_MapTable.find(id) ;
	if( it != m_MsgID_MsgDeser_MapTable.end() )
		return false;
	m_MsgID_MsgDeser_MapTable[id] = pMsgDes;
	return true;
}

bool CLChatServerReceiveMessage::ChatServerReceiveMessageRun( void* pContext )
{
	CLMessageQueue* pDealMsgQueue = (CLMessageQueue*)pContext;
	if( false == Initialize() )
		return false;

	CLUDPCommunicate  udp;
	udp.Initial();
	char buff[BUFF_SIZE];

	while(true)
	{
		//接受信息
		int readlen = udp.Read(buff,BUFF_SIZE);

		//对信息进行反序列化
        unsigned long id = *(unsigned long*)(buff + sizeof( int ) );
		std::map<long , CLMessageDeserializer*>::iterator it;
		it = m_MsgID_MsgDeser_MapTable.find(id);
		if( it != m_MsgID_MsgDeser_MapTable.end() )
			return false;
		CLMessage* pMsg = it->second->Deserialize(buff+sizeof(int));

		//把信息加入队列
        if ( false == pDealMsgQueue->PushMessage(pMsg) )
			return false;
	}

}