// VisualizeBinaryTreeTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../Tool/BinaryTreeVisualizor.h"
#include "../include/Hoffman.h"
#include <iostream>

using namespace MyDataStructure;
using namespace MyTools;
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	char values[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j' };
	float weights[] = { 0.24f, 0.84f, 0.03f, 0.51f, 0.12f, 0.79f, 0.93f, 0.34f, 0.61f, 0.46f };
	HoffmanTree<char, float> H(values, weights, 10);
	BinaryTreeVisualizor<HoffmanTree<char, float>::NodeType> btv(6.0f, 8.0f, 5.0f);
	btv.VisulizeTree(H.GetHead());
	cout << btv.GetLeft() << endl;
	cout << btv.GetRight() << endl;
	cout << btv.GetHeight() << endl;
	return 0;
}

