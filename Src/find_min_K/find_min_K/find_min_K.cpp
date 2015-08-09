// find_min_K.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <set>
#include <iostream>

using namespace std;

bool find_min_k(int input[],int result[],int input_count,int output_count)
{
	if(input_count < output_count) return false;
	set<int> s;
	for (int i = 0; i < output_count; ++i)
	{
		s.insert(input[i]);
	}
	for (int i = output_count; i < input_count; ++i)
	{
		set<int>::iterator tempIt = --s.end();
		if(input[i] < *tempIt)
		{
			s.erase(tempIt);
			s.insert(input[i]);
		}
	}
	int i = 0;
	for (set<int>::iterator it = s.begin(); it != s.end(); ++it)
	{
		result[i++] = *it;
	}
	return true;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int myarray[] = {10,6,15,4,8,1,17,14,5,13,7,11,9,12,16};
	int m = 15;
	int n = 7;
	int *result = new int[n];
	if(find_min_k(myarray,result,m,n))
	{
		
		for (int i = 0; i < n; ++i)
		{
			cout<<result[i]<<endl;
		}
	}
	return 0;
}

