#ifndef  CLFUNCPROVIDERNAMESERVER_H
#define  CLFUNCPROVIDERNAMESERVER_H
#include "CLFunctionProvider.h"
#include <map>
#include <string>
using namespace std;
class  CLFuncProviderNameServer
{
public:
	static CLFuncProviderNameServer* GetInstance();
	bool  Register(const char* strName , CLFunctionProvider* pFunctionProvider );
	CLFunctionProvider* GetFunctionProvider( const char* strName );
private:
	CLFuncProviderNameServer();
	~CLFuncProviderNameServer();

private:
	std::map<string , CLFunctionProvider*> m_Name_FuncProvider;
	static CLFuncProviderNameServer*  m_Instance;
};

#endif