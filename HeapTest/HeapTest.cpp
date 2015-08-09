// HeapTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../include/Heap.h"
#include "../include/Functor.h"
#include <iostream>

using namespace MyDataStructure;
using namespace std;

//使用堆结构进行了排序操作

int _tmain(int argc, _TCHAR* argv[])
{
	int v[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	//建立一个最大堆
	Heap<int> maxHeap(v, 10);
	//建立一个最小堆
	Heap<int, greater<int>> minHeap(v, 10);
	int k = 0;
	int size = maxHeap.Size();
	
	//堆排序
	for (int i = 0; i < size;++i)
	{
		if (maxHeap.GetTop(k))
			cout << k << " ";
		maxHeap.RemoveTop();
	}
	cout << endl;

	for (int i = 0; i < size; ++i)
	{
		if (minHeap.GetTop(k))
			cout << k << " ";
		minHeap.RemoveTop();
	}
	cout << endl;

	int v1[] = { 11, 33,19, 17, 14, 12, 18, 20 };
	for (int i = 0; i < 8;++i)
	{
		maxHeap.Insert(v1[i]);
	}
	Heap<int> He1(maxHeap);
	Heap<int> He2 = He1;
	size = He2.Size();
	for (int i = 0; i < size; ++i)
	{
		if (He2.GetTop(k))
			cout << k << " ";
		He2.RemoveTop();
	}
	cout << endl;

	return 0;
}

