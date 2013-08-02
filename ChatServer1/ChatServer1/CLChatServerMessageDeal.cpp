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
	//���д�����Ϣ��ע��
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
	//���Ĵ��롣��������������������������������
	//���Ƚ��д�������ע��
	if ( false == Initialize() )
		return false;

	while( true )
	{
		//��DealMsgQueue�õ���Ϣ
	CLMessage* pMsg = m_pDealMsgQueue->GetMessage();
	if( pMsg == NULL )
		return false;

	//�ҵ���Ӧ�Ĵ�����
	std::map<int , CallBackForMessageLoop>::iterator it;
	it = m_MsgCallBackFunMapTable.find( pMsg->m_clMsgID );
	if( it == m_MsgCallBackFunMapTable.end() )
		return false;

	//���д���������Ϣ
	CallBackForMessageLoop pFunction = it->second;
	CLMessage*  pSendMsg = (m_pMsgObsever->*pFunction)( pMsg );
	if( pSendMsg == NULL )
	{
		return false;
	}

	//�ѷ��ص���Ϣ���͸����Ͷ���
	bool r = m_pSendMsgQueue->PushMessage(pSendMsg);
	if ( r == false )
		return false;
	}
}