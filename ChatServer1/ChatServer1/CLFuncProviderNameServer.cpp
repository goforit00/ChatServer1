#include "CLFuncProviderNameServer.h"
#include <string.h>
CLFuncProviderNameServer* CLFuncProviderNameServer::m_Instance = NULL;

CLFuncProviderNameServer* CLFuncProviderNameServer::GetInstance()
{
	if( m_Instance == NULL )
		m_Instance = new CLFuncProviderNameServer();
	return m_Instance;
}

CLFuncProviderNameServer::CLFuncProviderNameServer()
{
}

CLFuncProviderNameServer::~CLFuncProviderNameServer()
{
	//释放所有的map
}

bool CLFuncProviderNameServer::Register(const char* strName , CLFunctionProvider* pFunctionProvider )
{
	std::map<std::string , CLFunctionProvider*>::iterator it = m_Name_FuncProvider.find(strName);
	if( it != m_Name_FuncProvider.end() )
		return false;

	m_Name_FuncProvider[strName] = pFunctionProvider;

	return true;
}

CLFunctionProvider* CLFuncProviderNameServer::GetFunctionProvider(const char* strName )
{
	if( strName == NULL || strlen(strName) == 0 )
		return NULL;

	std::map<std::string , CLFunctionProvider*>::iterator it = m_Name_FuncProvider.find( strName );
	if( it == m_Name_FuncProvider.end() )
		return NULL;
	return it->second;
}
