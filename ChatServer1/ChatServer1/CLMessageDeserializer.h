#ifndef   CLMESSAGEDESERIALIZER_H
#define   CLMESSAGEDESERIALIZER_H

class  CLMessage;

//----------------------------------------------------------------------------------
//����
class  CLMessageDeserializer
{
public:
	CLMessageDeserializer();
	virtual ~CLMessageDeserializer();
public:
	virtual CLMessage* Deserialize(char* pBuffer) = 0;
};

//-----------------------------------------------------------------------------------
//����Ϊ����
class  CLAddMsgDeserializer :public CLMessageDeserializer
{
public:
	CLAddMsgDeserializer();
	virtual ~CLAddMsgDeserializer();

public:
	virtual CLMessage* Deserialize(char* pBuffer)��
};

#endif