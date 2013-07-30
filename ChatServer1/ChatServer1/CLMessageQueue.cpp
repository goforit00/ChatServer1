#include "CLMessageQueue.h"

CLMessageQueue::CLMessageQueue():m_Semaphone(0)
{
}

CLMessageQueue::~CLMessageQueue()
{
}

bool CLMessageQueue::PushMessage( CLMessage* pMsg )
{
	if( pMsg == NULL )
		return false;
	if( false == m_Mutex.Lock() )
		return false;
	m_MessageQueue.push( pMsg );
	if( false == m_Semaphone.V() )
		return false;
	if( false == m_Mutex.UnLock() )
		return false;

	return true;
}

CLMessage* CLMessageQueue::GetMessage()
{
	if( m_Semaphone.P() == false )
		return NULL;
	if( false == m_Mutex.Lock() )
		return NULL;
	CLMessage* pMsg = m_MessageQueue.front();
	m_MessageQueue.pop();
	if( false == m_Mutex.UnLock() )
		return NULL;
	return pMsg;
}