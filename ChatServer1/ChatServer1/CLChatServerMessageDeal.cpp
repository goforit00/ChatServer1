#include "CLChatServerMessageDeal.h"
#include <iostream>

CLChatServerMessageDeal::CLChatServerMessageDeal( CLMessageQueue* pDealMsgQueue , CLMessageQueue* pSendMsgQueue )
{
	if( pDealMsgQueue == NULL )
		throw " DealMsgQueue is NULL";
	m_pDealMsgQueue =pDealMsgQueue;
    if( pSendMsgQueue == NULL )
		throw " SendMsgQueue is NULL";
	m_pSendMsgQueue = pSendMsgQueue;
}

CLChatServerMessageDeal::~CLChatServerMessageDeal()
{
}

bool CLChatServerMessageDeal::Initialize()
{
	//进行处理消息的注册
	Register( ADD_MESSAGE_ID , (CallBackForMessageLoop)(&CLMessageObsever::On_AddMsg));


}

bool CLChatServerMessageDeal::Register( int MsgID , CallBackForMessageLoop pMsgProcessFunction )
{
	std::map<int ,CallBackForMessageLoop>::iterator it;
	it = m_MsgCallBackFunMapTable.find(MsgID);
	if( it != m_MsgCallBackFunMapTable.end() )
		return false;

	m_MsgCallBackFunMapTable[MsgID] = pMsgProcessFunction;
	return true;
}

bool CLChatServerMessageDeal::FuntionProviderRun(void* pContext)
{
	//核心代码。。。。。。。。。。。。。。。。。
	//首先进行处理函数的注册
	if ( false == Initialize() )
		return false;

	while( true )
	{
		//从DealMsgQueue得到消息
	CLMessage* pMsg = m_pDealMsgQueue->GetMessage();
	if( pMsg == NULL )
		return false;

	//找到相应的处理函数
	std::map<int , CallBackForMessageLoop>::iterator it;
	it = m_MsgCallBackFunMapTable.find( pMsg->m_clMsgID );
	if( it == m_MsgCallBackFunMapTable.end() )
		return false;

	//进行处理，返回消息
	CallBackForMessageLoop pFunction = it->second;
	CLMessage*  pSendMsg = (m_pMsgObsever->*pFunction)( pMsg );
	if( pSendMsg == NULL )
	{
		return false;
	}

	//把返回的消息发送给发送队列
	bool r = m_pSendMsgQueue->PushMessage(pSendMsg);
	if ( r == false )
		return false;
	}
}