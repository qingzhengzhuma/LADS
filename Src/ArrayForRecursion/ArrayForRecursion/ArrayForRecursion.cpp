// ArrayForRecursion.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

using namespace std;

double Fibonacci(int n)
{
	if(n == 0 || n == 1) return 1;
	return Fibonacci(n - 1) + Fibonacci(n - 2);
}

double Fibonacci_a(int n)
{
	if(n < 0) return -1;
	if(n == 0 || n == 1) return 1;
	int m = n + 1;
	double *fibo = new double[m];
	fibo[0] = fibo[1] = 1;
	for (int i = 2; i < m; ++i)
	{
		fibo[i] = fibo[i - 1] + fibo[i - 2];
	}
	return fibo[n];
}

double f(int i,int j, int k)
{
	if(i < 0 || j < 0 || k < 0) return -1;
	if(i == 0 || j == 0 || k == 0) return 1;
	return f(i - 1,j,k) + f(i,j - 1,k) + f(i,j,k - 1);
}


double f_a(int m,int n, int p)
{
	if(m < 0 || n < 0 || p < 0) return -1;
	if(m == 0 || n == 0 || p == 0) return 1;
	m++;
	n++;
	p++;
	double *f_array = new double[m*n*p];
	memset(f_array,0,m*n*p*sizeof(double));
	for (int j = 0; j < n; ++j)
	{
		for (int k = 0; k < p; ++k)
		{
			f_array[j*p + k] = 1;
		}
	}
	for (int i = 0; i < m; ++i)
	{
		for (int k = 0; k < p; ++k)
		{
			f_array[i*n*p + k] = 1;
		}
	}
	for (int i = 0; i < m; ++i)
	{
		for (int j = 0; j < p; ++j)
		{
			f_array[(i*n + j)*p] = 1;
		}
	}
	for (int k = 1; k < p; ++k)
	{
		for (int j = 1; j < n; ++j)
		{
			for (int i = 1; i < m; ++i)
			{
				f_array[(i*n + j)*p + k] = f_array[((i-1)*n + j)*p + k] + f_array[(i*n + j - 1)*p + k] + f_array[(i*n + j)*p + k - 1];
			}
		}
	}
	return f_array[m* n * p - 1];
}


int _tmain(int argc, _TCHAR* argv[])
{
	int n = 200;
	cout<<f_a(n,n,n)<<endl;
	return 0;
}

