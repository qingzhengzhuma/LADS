// AVLTreeTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "../../include/AVLTree.h"


using namespace MyDataStructure;
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	int v[] = { 1, 3, 3, 9, 7, 9, 4, 2, 8, 10 };
	AVLTree<int> st;
	st.UniqueInsert(v, 10);
	for (AVLTree<int>::iterator it = st.Last(); it != st.End(); --it)
		cout << *it << " ";
	cout << endl;
	AVLTree<int> st1(st);
	st = st;
	AVLTree<int>::iterator it1 = st.FindFirst(9), it2 = st.FindLast(9);
	cout << "they are " << (it1 == it2) << " : " << *it1 << " " << *it2 << endl;
	for (int i = 0; i < 10; ++i)
	{
		st.Erase(v[i]);
	}
	for (AVLTree<int>::iterator it = st.Last(); it != st.End(); --it)
		cout << *it << " ";
	cout << endl;

	for (AVLTree<int>::iterator it = st1.First(); it != st1.End(); ++it)
		cout << *it << " ";
	cout << endl;

	const int n = st.Size();
	cout << n << endl;
	const int m = st1.Size();
	cout << m << endl;
	st.Clear();
	cout << "DONE" << endl;
	return 0;
}