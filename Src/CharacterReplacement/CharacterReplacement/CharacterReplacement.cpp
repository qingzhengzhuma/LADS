// CharacterReplacement.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

const int bufsize = 1024;

void Replace(char** str, char target_char,const char* replace_str)
{
	int replace_str_len = strlen(replace_str);
	char* p = *str;
	int target_char_fre = 0;
	int str_len = 0;
	while(*p)
	{
		if(*p == target_char) ++target_char_fre;
		++str_len;
		++p;
	}
	int extend_count = target_char_fre * (replace_str_len - 1);
	char * q = p + extend_count;
	int j = 0;
	while(j <= str_len)
	{
		if(*p != target_char)
			*q-- = *p--;
		else
		{
			const char* r = &replace_str[replace_str_len - 1];
			int i = 0;
			while(i < replace_str_len)
			{
				*q-- = *r--;
				++i;
			}
			--p;
		}
		++j;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	char * str = new char[bufsize];
	strcpy(str," wo shi zhong guo ren!");
	Replace(&str,' ',"%20");
	cout<<str<<endl;
	return 0;
}

