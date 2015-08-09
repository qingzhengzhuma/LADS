// GetMaxSubSequence.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int GetMaxSubSequence(int* arrays,int n,int &start,int &end)
{

	int curMaxSum = INT_MIN;
	 start = -1;
	 end = -1;
	 int tempTotal = 0;
	for (int i = 0; i < n; ++i)
	{
		tempTotal += arrays[i];
		int total = tempTotal + curMaxSum;
		if(total > curMaxSum)
		{
			if(arrays[i] > total)
			{
				start = i;
				end = i;
				curMaxSum = arrays[i];
			}
			else
			{
				end = i;
				curMaxSum += tempTotal;
			}
			tempTotal = 0;
		}
	}
	return curMaxSum;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int arrays[] = {1, -2, 3, 10, -4, 7, 2, -5};
	int start = 0,end = 0;
	int maxVal = GetMaxSubSequence(arrays,8,start,end);
	cout<<maxVal<<endl;
	for (int i = start; i <= end;++i)
	{
		cout<<arrays[i]<<' ';
	}
	cout<<endl;
	return 0;
}

