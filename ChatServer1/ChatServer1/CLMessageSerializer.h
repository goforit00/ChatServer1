#ifndef   CLMESSAGESERIALIZER_H
#define   CLMESSAGESERIALIZER_H

class CLMessage;
//����
class  CLMessageSerializer
{
public:
	CLMessageSerializer();
    virtual ~CLMessageSerializer();

public:
	virtual char* Serialize( CLMessage* pMsg , unsigned int* pFullLength , unsigned int HeadLength )= 0;
};

//----------------------------------------------------------------------------------------
//����Ϊ����
class  CLAddMsgSerializer :public CLMessageSerializer
{
public:
    CLAddMsgSerializer();
	virtual ~CLMessageSerializer();

	virtual char* Serialize( CLMessage* pMsg , unsigned int* pFullLength , unsigned int HeadLength );
};

class  CLAddResultMsgSerializer: public CLMessageSerializer
{
public:
	CLAddResultMsgSerializer();
	virtual ~CLAddResultMsgSerializer();

	virtual char* Serialize( CLMessage* pMsg , unsigned int* pFullLength , unsigned int HeadLength );
};

#endif