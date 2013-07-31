#include "CLMessage.h"

//--------------------------------------------------------------------------------------
CLMessage::CLMessage( unsigned long MsgID ):m_clMsgID(m_lMsgID),m_lMsgID( MsgID )
{

}

CLMessage::~CLMessage()
{
}

//------------------------------------------------------------------------------------------
//CLAddMessage
CLAddMessage::CLAddMessage():CLMessage(ADD_MESSAGE_ID)
{
}

CLAddMessage::~CLMessage
{
};

//--------------------------------------------------------------------------------------
//CLAddResultMessage
CLAddResultMessage::CLAddResultMessage(): CLMessage( ADD_RESULT_MESSAGE_ID )
{
}

CLAddResultMessage::~CLMessage
{
};