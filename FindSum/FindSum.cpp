// FindSum.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../Tool/Sorter.h"
#include <iostream>
using namespace MyTools;
using namespace std;

int CanFindSum(int A[], int start, int end, int sum)
{
	Sorter<int> sorter;
	sorter.ThreeWayQuickSort(A, start, end);
	int p = start, q = end;
	int count = 0;
	while (p < q)
	{
		int s = A[p] + A[q];
		if (s > sum) --q;
		if (s < sum) ++p;
		else
		{
			++count;
			--q;
			++p;
		}
	}
	return count;
}

void merge_for_reverse_order(int A[], int p, int q, int r, int& count)
{
	int length1 = q - p + 1, length2 = r - q;
	int * left = new int[length1],
		*right = &A[q + 1];
	for (int i = p, j = 0; j < length1;)
	{
		left[j++] = A[i++];
	}
	int left_count = length1;
	int i = 0, j = 0;
	while (i < length1 && j < length2)
	{
		if (left[i] <= right[j])
		{
			A[p++] = left[i++];
			--left_count;
		}
		else
		{
			A[p++] = right[j++];
			count += left_count;
		}
	}
	while (i < length1) A[p++] = left[i++];
	delete left;
}

void getInverseOrderCount(int A[], int start, int end,int &count)
{
	if (start < end)
	{
		int q = (start + end) / 2;
		getInverseOrderCount(A, start, q, count);
		getInverseOrderCount(A, q + 1, end, count);
		merge_for_reverse_order(A, start, q, end, count);
	}
}

int GetInverseOrderCount(int A[], int start, int end)
{
	int count = 0;
	getInverseOrderCount(A, start, end, count);
	return count;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int v1[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	int sum = 100, sum1 = 11;
	cout <<"逆序对数："<< GetInverseOrderCount(v1,0,9) << endl;
	cout << "相加之和等于100的数对个数："<<CanFindSum(v1, 0, 9, sum) << endl;
	cout << "相加之和等于11的数对个数：" << CanFindSum(v1, 0, 9, sum1) << endl;
	cout << endl;
	return 0;
}

