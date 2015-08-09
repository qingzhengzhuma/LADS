// HoffmanTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../include/Hoffman.h"
#include "../Tool/Painter.h"
#include <iostream>

using namespace MyDataStructure;
using namespace MyTools;
using namespace std;


int _tmain(int argc, _TCHAR* argv[])
{
	char values[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i','j' };
	float weights[] = { 0.24f, 0.84f, 0.03f, 0.51f, 0.12f, 0.79f, 0.93f, 0.34f, 0.61f, 0.46f };
	HoffmanTree<char, float> H(values,weights,10);
	HoffmanTree<char, float> H1(H);
	HoffmanTree<char, float> H2 = H1;
	float sum = 0.0f;
	for (int i = 0; i < 10; ++i)
	{
		sum += weights[i];
	}
	cout << sum << endl;
	Painter<MemoryImgDevice<unsigned char, int>> p(8,8,1);
	cout << p.GetWidth()<< endl;
	cout << p.GetChannelCount()<< endl;
	cout << p.GetHeight() << endl;
	p.DrawPoint(4, 5);
	p.DrawLine(0, 0, 7, 7);
	p.DrawCircle(3, 3, 3);
	for (int i = 0; i < p.GetHeight();++i)
	{
		for (int j = 0; j < p.GetWidth(); ++j)
		{
			cout << int(p.GetImgData()[i*p.GetWidth() + j]) ;
		}
		cout << endl;
	}
	return 0;
}

