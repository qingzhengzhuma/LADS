// selfadjustlist.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

const int null_slot = -2;
const int end_slot = -1;

struct list_node
{
	int val;
	int next;
};

struct self_adjust_list
{
	int capacity;
	int size;
	int head;
	list_node* vals;
};

self_adjust_list* create(int capacity)
{
	self_adjust_list* sal = new self_adjust_list;
	sal->vals = new list_node[capacity];
	memset(sal->vals,0,capacity*sizeof(list_node));
	for (int i = 0; i < capacity; ++i)
	{
		sal->vals[i].next = null_slot;
	}
	sal->size = 0;
	sal->head = 0;
	sal->capacity = capacity;
	return sal;
}

bool find(self_adjust_list** sal,int val)
{
	if((*sal)->size == 0) return false;
	int cur = (*sal)->head;
	list_node* p = (*sal)->vals;
	int pre = -1;
	while(cur != end_slot && p[cur].val != val)
	{
		pre = cur;
		cur = p[cur].next;
	}
	if(cur == (*sal)->head) return true;
	if(cur != end_slot)
	{
		p[pre].next = p[cur].next;
		p[cur].next = (*sal)->head;
		(*sal)->head = cur;
		return true;
	}
	return false;
}

void push(self_adjust_list** sal,int val)
{
	if(find(sal,val)) return;

	if((*sal)->size == 0)
	{
		(*sal)->vals[0].val = val;
		(*sal)->vals[0].next = end_slot;
		
	}
	else
	{
		int i = 0;
		for (; i < (*sal)->capacity; ++i)
		{
			if((*sal)->vals[i].next == null_slot)
				break;
		}
		(*sal)->vals[i].next = (*sal)->head;
		(*sal)->vals[i].val = val;
		(*sal)->head = i;
	}
	
	++(*sal)->size;
}

bool pop(self_adjust_list** sal,int &val)
{
	if((*sal)->size < 1) return false;

	list_node* p = &(*sal)->vals[(*sal)->head];
	val = p->val;
	if((*sal)->size > 1)
	{
		(*sal)->head = p->next;
		p->next = null_slot;
	}
	else
	{
		(*sal)->head = 0;
	}
	--(*sal)->size;
	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	self_adjust_list* sal = create(20);
	for (int i = 1; i < 6; ++i)
		push(&sal,i);
	cout<<sal->size<<endl;
	for (int i = 10; i > 0; --i)
	{
		cout<<find(&sal,i)<<' ';
	}
	cout<<endl;
	for (int i = 1; i < 20; ++i)
	{
		int val;
		if(pop(&sal,val))
			cout<<val<<' ';
	}
	cout<<endl;
	cout<<sal->size<<endl;
	return 0;
}

