// BitMapSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

void sort(int *array,int value_count,int min_value,int max_value)
{
	if(min_value >= max_value) return;
	int bit_map_count = (max_value - min_value + 1 + 7) / 8;
	unsigned char* bit_map  = new unsigned char[bit_map_count];
	memset(bit_map,0,bit_map_count*sizeof(unsigned char));
	int* p = array;
	for (int i = 0; i < value_count; ++i,++p)
	{
		int value = *p - min_value;
		int index = value >> 3;
		int pos_in_byte = value % 8;
		bit_map[index] = bit_map[index] | (128>>pos_in_byte);
	}
	p = array;
	for (int i = 0; i < bit_map_count; ++i)
	{
		unsigned char c = bit_map[i];
		for (int j = 0; j < 8; ++j)
		{
			if( c & (128>>j))
			{
				*p = (i<<3) + j + min_value;
				++p;
			}
		}
	}
}


int _tmain(int argc, _TCHAR* argv[])
{
	int n = 10;
	int array[] = {0,-1,-2,-3,-4,-5,-6,-7,-8,-9};
	for (int i = 0; i < n; ++i)
	{
		cout<<array[i]<<' ';
	}
	cout<<endl;
	sort(array,n,-9,98);
	for (int i = 0; i < n; ++i)
	{
		cout<<array[i]<<' ';
	}
	cout<<endl;
}

