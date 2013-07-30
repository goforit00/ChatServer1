#ifndef  CLMESSAGE_H
#define  CLMESSAGE_H

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

#endif