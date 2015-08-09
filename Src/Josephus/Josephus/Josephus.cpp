// Josephus.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct person
{
	int id;
	person* next;
};

struct person_list
{
	int count;
	person* first;
	person* last;
};

person_list* init(int n)
{
	person* p = new person[n];
	for (int i = 0; i < n - 1; ++i)
	{
		p[i].id = i + 1;
		p[i].next = &p[i+1];
	}
	p[n - 1].id = n;
	p[n - 1].next = &p[0];
	person_list* persons = new person_list;
	persons->count = n;
	persons->first = p;
	persons->last = &p[n - 1];
	return persons;
}

int* solve(int n,int m)
{
	if(n < 1 || m < 0) return NULL;
	person_list* persons = init(n);
	person* first = persons->first;
	person* t = first;
	int count = persons->count;
	int *losers = new int[n];
	int j = 0;
	while(count > 1)
	{
		person* q = NULL;
		for (int i = 0; i < m; ++i)
		{
			q = first;
			first = first->next;
		}
		if(first == persons->first)
		{
			persons->first = first->next;
			persons->last =  persons->first;
		}
		else if(first == persons->last)
		{
			q->next = first->next;
			persons->last = q;
		}
		else
		{
			q->next = first->next;
		}
		--count;
		losers[j++] = first->id;
		first = first->next;
	}
	losers[j] = persons->first->id;
	delete []t;
	delete persons;
	return losers;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int n = 5, m = 1;
	int* losers = solve(n,m);
	for (int i = 0; i < n; ++i)
	{
		cout<<losers[i]<<' ';
	}
	cout<<endl;
	delete[]losers;
	return 0;
}

