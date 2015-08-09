// RBTreeTest.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "../include/RBTree.h"
#include <iostream>
using namespace std;

using namespace MyDataStructure;


int _tmain(int argc, _TCHAR* argv[])
{
	int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	RBTree<int> rb;
	for (int i = 0; i < 10; ++i)
	{
		rb.Insert(array[i]);
	}
	for (RBTree<int>::iterator it = rb.Last(); it != rb.End(); --it)
	{
		cout << *it << ' ';
	}
	cout << endl;
	for (int i = 0; i < 9; ++i)
	{
		rb.Erase(array[i]);
	}
	for (RBTree<int>::iterator it = rb.First(); it != rb.End(); ++it)
	{
		cout << *it << ' ';
	}
	cout << endl;
	return 0;
}

