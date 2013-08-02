#ifndef  CLCHATSERVERRECEIVEMESSAGE_H
#define  CLCHATSERVERRECEIVEMESSAGE_H

class CLMessageQueue;
class  CLChatServerReceiveMessage
{
public:
	CLChatServerReceiveMessage(CLMessageQueue* pDealMsgQueue);
	~CLChatServerReceiveMessage();

	bool ChatServerReceiveMessageRun( void* pContext );
    bool Initialize();
	bool Register( unsigned long id , CLMessageDeserializer *pMsgDes );
private:
	CLMessageQueue* m_pDealMsgQueue;
	std::map<unsigned long ID , CLMessageDeserializer* pMsgDeserializer> m_MsgID_MsgDeser_MapTable;
};

#endif