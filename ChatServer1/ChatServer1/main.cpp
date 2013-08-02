#include <iostream>
#include <unistd.h>
#include <pthread.h>
#include <queue>
#include <map>
#include <semaphore.h>
#include <string.h>
#include <string>
#include "CLFuncProviderNameServer.h"
#include "CLFunctionProvider.h"
#include "CLMessage.h"
#include "CLMutex.h"
#include "CLSemaphore.h"
#include "CLThread.h"
#include "CLThreadPool.h"
#include "CLMessageQueue.h"
using namespace std;

#define  BUFF_SIZE  256

int main()
{
	//��������
	CLMessageQueue  *pDealQueue = (CLMessageQueue*)_Malloc( sizeof( CLMessageQueue) );
	CLMessageQueue  *pSendQueue = (CLMessageQueue*)_Malloc( sizeof( CLMessageQueue) );

	//ע�ᴦ���߳�
	CLFuncProviderNameServer* pfpns = CLFuncProviderNameServer::GetInstance();
	pfpns->Register( "DealMsg",new  CLChatServerMessageDeal(pDealQueue , pSendQueue) ); 

	//�ô����߳���������
	CLThreadPool* pThreadPool_DealMsg = new CLThreadPool(5,"DealMsg");
	pThreadPool_DealMsg->ThreadsRun(NULL);

	//���������߳�
	pfpns->Register("SendMsg", new CLChatServerMessageSend(pSendQueue) );
	
	//�÷����߳���������
	CLThreadPool* pThreadPool_SendMsg = new CLThreadPool(1 , "SendMsg");
	pThreadPool_SendMsg->ThreadsRun(NULL);

	//���߳̽�����Ϣ�Ľ���
    CLChatServerReceiveMessage *pChatRecMsg = new CLChatServerReceiveMessage();
	pChatRecMsg->ChatServerReceiveMessageRun((void*)pDealQueue);


	pthread_exit(NULL);
}