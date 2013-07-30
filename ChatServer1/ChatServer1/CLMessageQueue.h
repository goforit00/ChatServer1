#ifndef  CLMESSAGEQUEUE_H
#define  CLMESSAGEQUEUE_H

class  CLMessageQueue
{
public:
	CLMessageQueue();
	~CLMessageQueue();

public:
	bool PushMessage( CLMessage* pMsg );
	CLMessage* GetMessage();

private:
	std::queue<CLMessage*> m_MessageQueue;
	CLSemaphore m_Semaphone;
	CLMutex m_Mutex;
};


#endif