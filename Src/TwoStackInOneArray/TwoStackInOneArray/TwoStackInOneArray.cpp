// TwoStackInOneArray.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;


struct special_stack
{
	int capcity;
	int ltop,rtop;
	int* vals;
};

special_stack* create(int capacity)
{
	special_stack* sstack = new special_stack;
	sstack->vals = new int[capacity];
	sstack->capcity = capacity;
	sstack->ltop = -1;
	sstack->rtop = capacity;
	return sstack;
}

bool lpush(special_stack** sstack,int val)
{
	if((*sstack)->ltop + 1 == (*sstack)->rtop) return false;
	(*sstack)->vals[++((*sstack)->ltop)] = val;
	return true;
}

bool lpop(special_stack** sstack,int& val)
{
	if((*sstack)->ltop < 0) return false;
	val = (*sstack)->vals[((*sstack)->ltop)--];
	return true;
}

bool rpush(special_stack** sstack,int val)
{
	if((*sstack)->rtop - 1 == (*sstack)->ltop) return false;
	(*sstack)->vals[--((*sstack)->rtop)] = val;
	return true;
}

bool rpop(special_stack** sstack,int& val)
{
	if((*sstack)->rtop >= (*sstack)->capcity) return false;
	val = (*sstack)->vals[((*sstack)->rtop)++];
	return true;
}

void destroy(special_stack** sstack)
{
	delete [](*sstack)->vals;
	delete (*sstack);
	*sstack = NULL;
}

void clear(special_stack** sstack)
{
	(*sstack)->ltop = -1;
	(*sstack)->rtop = (*sstack)->capcity;
}


int _tmain(int argc, _TCHAR* argv[])
{
	special_stack* stack = create(20);
	for (int i = 1; i <= 10; ++i)
	{
		lpush(&stack,i);
		rpush(&stack,i + 10);
	}
	for (int i = 1; i <= 10; ++i)
	{
		int val;
		if(lpop(&stack,val))
			cout<<val<<' ';
	}
	cout<<endl;
	for (int i = 1; i <= 10; ++i)
	{
		int val;
		if(rpop(&stack,val))
			cout<<val<<' ';
	}
	cout<<endl;

	for (int i = 1; i <= 10; ++i)
	{
		lpush(&stack,i);
		rpush(&stack,i + 10);
	}

	cout<<lpush(&stack,21)<<endl;
	cout<<rpush(&stack,31)<<endl;

	int val;
	lpop(&stack,val);
	rpop(&stack,val);
	cout<<lpush(&stack,21)<<endl;
	cout<<rpush(&stack,31)<<endl;
	destroy(&stack);
	return 0;
}

