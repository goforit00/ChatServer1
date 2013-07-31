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


int main()
{
	CLFuncProviderNameServer* pfpns = CLFuncProviderNameServer::GetInstance();
	pfpns->Register( "print",new  ); 

	CLThreadPool* pthreadpool = new CLThreadPool(5,"print");
	long temp = 5;
	pthreadpool->ThreadsRun((void*)&temp);
	sleep(1);
	cout<<temp<<endl;
	//    sleep(3);
	pthread_exit(NULL);
}