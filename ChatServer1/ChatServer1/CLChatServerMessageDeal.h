#ifndef   CLCHATSERVERMESSAGEDEAL_H
#define   CLCHATSERVERMESSAGEDEAL_H
#include "CLMessageObsever.h"

typedef  bool  (CLMessageObsever::*CallBackForMessageLoop)(CLMessage*);

class  CLChatServerMessageDeal : public CLFunctionProvider
{
public: 
	CLChatServerMessageDeal( CLMessageQueue* pDealMsgQueue , CLMessageQueue* pSendMsgQueue );
	virtual ~CLChatServerMessageDeal();
	virtual bool FuntionProviderRun(void* pContext);
	virtual bool Initialize() ;
	bool  Register( int MsgID , CallBackForMessageLoop pMsgProcessFunction );

private:
	CLMessageQueue*  m_pDealMsgQueue;
	CLMessageQueue*  m_pSendMsgQueue;

	CLMessageObsever* m_pMsgObsever;
	std::map<int MsgID , CallBackForMessageLoop> m_MsgCallBackFunMapTable;
};

#endif