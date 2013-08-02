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
	//创建队列
	CLMessageQueue  *pDealQueue = (CLMessageQueue*)_Malloc( sizeof( CLMessageQueue) );
	CLMessageQueue  *pSendQueue = (CLMessageQueue*)_Malloc( sizeof( CLMessageQueue) );

	//注册处理线程
	CLFuncProviderNameServer* pfpns = CLFuncProviderNameServer::GetInstance();
	pfpns->Register( "DealMsg",new  CLChatServerMessageDeal(pDealQueue , pSendQueue) ); 

	//让处理线程运行起来
	CLThreadPool* pThreadPool_DealMsg = new CLThreadPool(5,"DealMsg");
	pThreadPool_DealMsg->ThreadsRun(NULL);

	//创建发送线程
	pfpns->Register("SendMsg", new CLChatServerMessageSend(pSendQueue) );
	
	//让发送线程运行起来
	CLThreadPool* pThreadPool_SendMsg = new CLThreadPool(1 , "SendMsg");
	pThreadPool_SendMsg->ThreadsRun(NULL);

	//主线程进程消息的接收
    CLChatServerReceiveMessage *pChatRecMsg = new CLChatServerReceiveMessage();
	pChatRecMsg->ChatServerReceiveMessageRun((void*)pDealQueue);


	pthread_exit(NULL);
}