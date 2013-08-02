#ifndef  CLMESSAGEOBSEVER_H
#define  CLMESSAGEOBSEVER_H

class  CLMessageObsever
{
public:
	CLMessageObsever();
	~CLMessageObsever();

public:
	CLMessage* On_AddMsg( CLMessage *pMsg );
};

#endif