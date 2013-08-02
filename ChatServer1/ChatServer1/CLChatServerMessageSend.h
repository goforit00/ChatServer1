#ifndef   CLCHATSERVERMESSAGESEND_H
#define   CLCHATSERVERMESSAGESEND_H
#include "CLMessageSerializer.h"
class CLChatServerMessageSend : public CLFunctionProvider
{
public:
	CLChatServerMessageSend( CLMessageQueue* pSendMsgQueue );
	virtual ~CLChatServerMessageSend();

	virtual bool CLFunctionProvider(void* pContext);
	virtual bool Initialize();
	bool Register( unsigned long id , CLMessageSerializer* MsgSer );

private:
	CLMessageQueue* m_pSendMsgQueue;
	std::map<unsigned long ID , CLMessageSerializer* MsgSer> m_MsgID_MsgSer_MapTable;
};

#endif