#ifndef  CLFUNCTIONPROVIDER_H
#define  CLFUNCTIONPROVIDER_H

class CLFunctionProvider
{
public:
	CLFunctionProvider();
	virtual ~CLFunctionProvider();

	virtual bool FuntionProviderRun(void* pContext) = 0 ;
};

#endif