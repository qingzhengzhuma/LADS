// Vector.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../../include/Vector.h"
#include "../../include/Action.h"
#include "../../include/Func.h"
#include <iostream>

using namespace MyDataStructure;
using namespace std;

void g1(int a, int b)
{
	cout << a + b << endl;
}

void g2(int a, int b)
{
	cout << a - b << endl;
}

void g3(int a, int b)
{
	cout << a * b << endl;
}

void f1(int p)
{
	cout << p << endl;
}

void f2(int p)
{
	cout << p*2 << endl;
}

void f3(int p)
{
	cout << p * 3 << endl;
}

int F1()
{
	return 5;
}

int F2()
{
	return 10;
}

int F3()
{
	return 15;
}

void Fv1()
{
	cout << 100 << endl;
}

void Fv2()
{
	cout << 200 << endl;
}

void Fv3()
{
	cout << 300 << endl;
}


int _tmain(int argc, _TCHAR* argv[])
{
	Action<int> ac;
	ac += f1;
	ac += f2;
	ac += f3;
	ac(4);
	ac -= f1;
	ac(5);

	Action<> acv;
	acv += Fv3;
	acv += Fv2;
	acv += Fv1;
	acv();

	Action<int, int> cal;
	cal += g1;
	cal += g2;
	cal += g3;
	cal(50, 30);
	cal -= g3;
	cal(50, 30);

	Func<int> fu;
	fu += F1;
	fu += F2;
	fu += F3;
	Vector<int> v = fu();
	for (Vector<int>::iterator i = v.First(); i != v.End(); ++i)
	{
		cout << *i << ' ';
	}
	cout << endl;
	fu -= F1;
	v = fu();
	for (Vector<int>::iterator i = v.First(); i != v.End(); ++i)
	{
		cout << *i << ' ';
	}
	cout << endl;
	return 0;
}

