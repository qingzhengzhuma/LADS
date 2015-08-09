// UnionFindSetTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../include/UnionFindSet.h"
#include <iostream>

using namespace MyDataStructure;
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	UnionFindSet ufs(21);
	ufs.Union(0, 1);
	ufs.Union(3, 1);
	ufs.Union(2, 3);
	ufs.Union(15, 19);
	ufs.Union(15, 2);
	cout << ufs.Find(0) << endl;
	cout << ufs.Find(1) << endl;
	cout << ufs.Find(2) << endl;
	cout << ufs.Find(3) << endl;
	cout << ufs.Find(91) << endl;
	cout << ufs.Find(19) << endl;
	cout << ufs.Find(15) << endl;

	return 0;
}

