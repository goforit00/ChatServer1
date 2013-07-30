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


class CLPrint :public CLFunctionProvider
{
public:
	CLPrint();
	~CLPrint();

public:
	virtual bool FuntionProviderRun(void* pContext);
};

CLPrint::CLPrint()
{
}

CLPrint::~CLPrint()
{
}
bool CLPrint::FuntionProviderRun(void* pContext)
{
	cout<<"in thread"<<endl;
	long *pl =(long*)pContext;
	*pl=(*pl)+1;
	cout<<*(long*)pContext<<endl;
}


//----------------------------------------------------------------------------

class  CLMessageObsever
{
public:
	bool On_XXXMsg( CLMessage *pMsg );

};

typedef  bool  (CLMessageObsever::*CallBackForMessageLoop)(CLMessage*);

class  CLChatServerMessageDeal : public CLFunctionProvider
{
public: 
	CLChatServerMessageDeal( CLMessageQueue* pDealMsgQueue , CLMessageQueue* pSendMsgQueue );
    virtual ~CLChatServerMessageDeal();
	virtual bool FuntionProviderRun(void* pContext);
private:
    CLMessageQueue*  m_pDealMsgQueue;
	CLMessageQueue*  m_pSendMsgQueue;

	CLMessageObsever* m_pMsgObsever;
	std::map<int MsgID , CallBackForMessageLoop> m_MsgCallBackFunMapTable;
};


int main()
{
	CLFuncProviderNameServer* pfpns = CLFuncProviderNameServer::GetInstance();
	pfpns->Register( "print",new CLPrint() ); 

	CLThreadPool* pthreadpool = new CLThreadPool(5,"print");
	long temp = 5;
	pthreadpool->ThreadsRun((void*)&temp);
	sleep(1);
	cout<<temp<<endl;
	//    sleep(3);
	pthread_exit(NULL);
}