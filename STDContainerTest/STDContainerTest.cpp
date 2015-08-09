// STDContainerTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <queue>

using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	queue<int> q;
	q.push(1);
	q.push(2);
	int v = q.front();
	cout << v << endl;
	q.pop();
	v = q.front();
	cout << v << endl;
	cout << q.empty()<<endl;
	q.pop();
	cout << q.empty() << endl;
	return 0;
}

