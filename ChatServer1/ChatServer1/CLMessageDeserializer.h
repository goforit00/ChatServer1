#ifndef   CLMESSAGEDESERIALIZER_H
#define   CLMESSAGEDESERIALIZER_H

class  CLMessage;

//----------------------------------------------------------------------------------
//父类
class  CLMessageDeserializer
{
public:
	CLMessageDeserializer();
	virtual ~CLMessageDeserializer();
public:
	virtual CLMessage* Deserialize(char* pBuffer) = 0;
};

//-----------------------------------------------------------------------------------
//以下为子类
class  CLAddMsgDeserializer :public CLMessageDeserializer
{
public:
	CLAddMsgDeserializer();
	virtual ~CLAddMsgDeserializer();

public:
	virtual CLMessage* Deserialize(char* pBuffer)；
};

#endif