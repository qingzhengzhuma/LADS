// SorterTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../Tool/Sorter.h"
#include <iostream>
using namespace MyTools;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int v1[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	Sorter<int> sorter;
	sorter.BufferSort(v1, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v1[i] << ' ';
	}
	cout << endl;

	int v2[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	sorter.InsertSort(v2, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v2[i] << ' ';
	}
	cout << endl;

	int v3[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	sorter.BinaryInsertSort(v3, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v3[i] << ' ';
	}
	cout << endl;

	int v4[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	sorter.ShellSort(v4, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v4[i] << ' ';
	}
	cout << endl;

	int v5[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	sorter.QuickSort(v5, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v5[i] << ' ';
	}
	cout << endl;

	int v6[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	sorter.RandomizedQuickSort(v6, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v6[i] << ' ';
	}
	cout << endl;

	int v7[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	sorter.Median3QuickSort(v7, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v7[i] << ' ';
	}
	cout << endl;

	int v8[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	sorter.HybridQuickSort(v8, 0, 9,5);
	for (int i = 0; i < 10; ++i)
	{
		cout << v8[i] << ' ';
	}
	cout << endl;

	int v9[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	sorter.SelectSort(v9, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v9[i] << ' ';
	}
	cout << endl;

	int v10[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	sorter.HeapSort(v10, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v10[i] << ' ';
	}
	cout << endl;

	int v11[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	sorter.MergeSort(v11, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v11[i] << ' ';
	}
	cout << endl;

	Sorter<int, MyDataStructure::greater<int>> sorter1;
	sorter1.MergeSort(v11, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v11[i] << ' ';
	}
	cout << endl;

	sorter.ThreeWayQuickSort(v11, 0, 9);
	for (int i = 0; i < 10; ++i)
	{
		cout << v11[i] << ' ';
	}
	cout << endl;

	return 0;
}

