// PrintN.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;


void __print(char digit_array[], int index, int n)
{
	if (index < 0) return;
	if (index == n - 1)
	{
		digit_array[index] = '0';
		for (int i = 0; i < 10; ++i)
		{
			digit_array[index] = i + '0';
			cout << digit_array << endl;
		}
		return;
	}
	if (digit_array[index] != ' ')
		digit_array[index] = '0';
	__print(digit_array, index + 1, n);
	for (int i = 1; i < 10; ++i)
	{
		digit_array[index] = i + '0';
		__print(digit_array, index + 1, n);
	}
}
void PrintN(int n)
{
	char *digit_array = new char[n + 1];
	for (int i = 0; i < n; ++i)
	{
		digit_array[i] = ' ';
	}
	digit_array[n] = '\0';
	__print(digit_array, 0, n);
	delete[]digit_array;
}

int _tmain(int argc, _TCHAR* argv[])
{
	PrintN(4);
	return 0;
}

