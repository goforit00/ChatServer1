#ifndef CLDATE_H
#define CLDATE_H

#include<sys/types.h>


class CLDate
{
	public:
		static CLDate* GetInstance();
        int GetDate(char* pstrDate , size_t strlen );//返回日期字符串的长度
	private:
		CLDate();
		~CLDate();

		CLDate(const CLDate&);
		CLDate& operator =(const CLDate&);
        
	private:
		static CLDate* m_Instance;
};

#endif
