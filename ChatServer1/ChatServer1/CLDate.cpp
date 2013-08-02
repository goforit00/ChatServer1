#include<time.h>
#include<stdio.h>
#include<iostream>
#include"CLDate.h"
using namespace std;

CLDate* CLDate::m_Instance = NULL;

CLDate* CLDate::GetInstance()
{
	if( m_Instance == NULL )
	  m_Instance = new CLDate();
	return m_Instance;
}

CLDate::CLDate()
{

}
CLDate::~CLDate()
{

}

int CLDate::GetDate(char* pstrDate , size_t strlen )
{
    time_t tmptime;
	time(&tmptime);
    int len = snprintf( pstrDate , strlen ,"%s ",ctime(&tmptime));
	pstrDate[len-1] =' ';
	pstrDate[len-2] =' ';
	return len;
}

int GetDateTime( char* pDateTime , size_t strlen )
{
	static CLDate *pDate = CLDate::GetInstance();
	return pDate->GetDate(pDateTime , strlen );
}
