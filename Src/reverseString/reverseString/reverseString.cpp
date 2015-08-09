// reverseString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string.h>
#include <iostream>
#include <vector>


using namespace std;

void ReverseString(char str[],int start,int end)
{
	for (int i = start,j = end; i < j; ++i,--j)
	{
		char c = str[i];
		str[i] = str[j];
		str[j] = c;
	}
}

void ReverseString(char str[])
{
	int length = strlen(str);
    ReverseString(str,0,length - 1);
}

void ReverseSentence(char str[])
{
	ReverseString(str);
	vector<int> splitIndex;
	int length = strlen(str);
	splitIndex.push_back(-1);
	for (int i = 0; i < length; ++i)
	{
		if(str[i] == ' ')
			splitIndex.push_back(i);
	}
	splitIndex.push_back(length);
	int count = splitIndex.size() - 1;
	for (int i = 0; i < count; ++i)
	{
		ReverseString(str,splitIndex[i] + 1,splitIndex[i+1] - 1);
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	char str[] = "wo shi zhong guo ren";
	cout<<str<<endl;
	ReverseSentence(str);
	cout<<str<<endl;
	return 0;
}

