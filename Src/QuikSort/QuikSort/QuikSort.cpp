// QuikSort.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

int partition(int array[],int start,int end)
{
	int pivot = array[start];
	while(start < end){
		while(start < end && array[end] >= pivot) --end;
		array[start] = array[end];
		while(start < end && array[start] <= pivot) ++start;
		array[end] = array[start];
	}
	array[start] = pivot;
	return start;
}

void qsort(int array[],int start,int end)
{
	if(start < end)
	{
		int pivot_index = partition(array,start,end);
		qsort(array,start,pivot_index - 1);
		qsort(array,pivot_index + 1,end);
	}
}

void QuickSort(int array[],int n)
{
	qsort(array,0,n - 1);
}


int _tmain(int argc, _TCHAR* argv[])
{
	const int N = 11;
	int array[] = {7,4,8,4,4,9,2,1,-7,-5,6};
	for (int i = 0; i < N; ++i)
	{
		cout<<array[i]<<' ';
	}
	cout<<endl;
	QuickSort(array,N);
	for (int i = 0; i < N; ++i)
	{
		cout<<array[i]<<' ';
	}
	cout<<endl;
	return 0;
}

