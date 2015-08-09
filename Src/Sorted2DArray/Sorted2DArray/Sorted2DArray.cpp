// Sorted2DArray.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

int* CreateSorted2DArray(int InputArray[],int InputCount,int Row,int Col)
{
	if(Row*Col != InputCount) return NULL;
	int* res = new int[InputCount];
	int SquareWidth = min(Row,Col);
	int index = 0;
	for (int i = 0; i < SquareWidth; ++i)
	{
		for (int j = 0; j < i; ++j)
		{
			res[i*Col + j] = InputArray[index++];
		}
		for (int j = 0; j < i; ++j)
		{
			res[j*Col + i] = InputArray[index++];
		}
		res[i*Col + i] = InputArray[index++];
	}
	if(SquareWidth == Row)
	{
		for (int j = SquareWidth; j < Col; ++j)
		{
			for (int i = 0; i < Row; ++i)
			{
				res[i*Col + j] = InputArray[index++];
			}
		}
	}
	else
	{
		for (int i = SquareWidth; i < Row; ++i)
		{
			for (int j = 0; j < Col; ++j)
			{
				res[i*Col + j] = InputArray[index++];
			}
		}
	}
	return res;
}


bool IsContained(const int Sorted2DArray[],const int Row,const int Col,const int value)
{
	int i = 0,j = Col - 1;
	while( i < Row && j >= 0)
	{
		int v = Sorted2DArray[i*Col + j];
		if( v == value) return true;
		else if( v < value)
		{
			if(i < Row) ++i;
		}
		else
		{
			if(j > 0) --j;
		}
	}
	return false;
}

int* CreateTestData(int Row,int Col)
{
	int EleCount = Row*Col;
	int *TestData = new int[EleCount];
	for (int i = 0; i < EleCount; ++i)
	{
		TestData[i] = i + 11;
	}
	return TestData;
}

void Display2DArray(int InputArray[],int Row,int Col)
{
	for (int i = 0; i < Row; ++i)
	{
		for (int j = 0; j < Col; ++j)
		{
			cout<<InputArray[i*Col + j]<<" ";
		}
		cout<<endl;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	cout<<"============Row = 8,Col = 5=============="<<endl;
	int m = 8,n = 5;
	int* TestData1 = CreateTestData(m,n);
	int* Sorted2DArray1 = CreateSorted2DArray(TestData1,m*n,m,n);
	Display2DArray(Sorted2DArray1,m,n);
	cout<<"============Row = 5,Col = 8=============="<<endl;
	m = 5,n = 8;
	int* TestData2 = CreateTestData(m,n);
	int* Sorted2DArray2 = CreateSorted2DArray(TestData2,m*n,m,n);
	Display2DArray(Sorted2DArray2,m,n);
	cout<<IsContained(Sorted2DArray2,m,n,100)<<endl;
	cout<<IsContained(Sorted2DArray1,n,m,46)<<endl;
	return 0;
}

