// Deque.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../../include/List.h"
#include <iostream>

using namespace std;

using namespace MyDataStructure;

int _tmain(int argc, _TCHAR* argv[])
{
	List<int> d;
	for (int i = 0; i < 10; ++i)
	{
		d.Insert(i);
	}
	List<int> d2;
	List<int> d1 = d2 = d;

	int value;
	for (int i = 0; i < 10; ++i)
	{
		if (d1.Eject(value))
			cout << value << ' ';
	}
	cout << endl;
	for (int i = 0; i < 10; ++i)
	{
		if (d2.Eject(value))
			cout << value << ' ';
	}
	cout << endl;
	for (int i = 0; i < 10; ++i)
	{
		if (d.Eject(value))
			cout << value << ' ';
	}
	cout << endl;
	cout << d.Size() << endl;
	d.Clear();
	d1.Clear();
	d2.Clear();
	return 0;
}

