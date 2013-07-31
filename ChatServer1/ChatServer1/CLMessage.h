#ifndef  CLMESSAGE_H
#define  CLMESSAGE_H

#define  ADD_MESSAGE_ID            1
#define  ADD_RESULT_MESSAGE_ID        2

class CLMessage
{
public:
	CLMessage( unsigned long MsgID );
	virtual ~CLMessage();

public:
	const unsigned long& m_clMsgID;

protected:
	unsigned long m_lMsgID;
};

//------------------------------------------------------------------------------------

class  CLAddMessage :public CLMessage
{
public:
	CLAddMessage();
	virtual ~CLAddMessage();

public:
	int  m_adder1;
	int  m_adder2;
};



//-------------------------------------------------------------------------------
class  CLAddResultMessage:public CLMessage
{
public:
	CLAddResultMessage();
	virtual ~CLAddResultMessage();

public:
	int  m_addresult;
};



#endif