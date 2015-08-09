// LoopQueue.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct loop_queue
{
	int capacity;
	int head;
	int tail;
	int *vals;
};

loop_queue* create(int capacity)
{
	loop_queue* lq = new loop_queue;
	lq->capacity = capacity;
	lq->vals = new int[capacity];
	lq->head = lq->tail = 0;
	return lq;
}

bool isEmpty(loop_queue* lq)
{
	if(lq->head == lq->tail) return true;
	return false;
}

bool isFull(loop_queue* lq)
{
	if((lq->tail + 1) % lq->capacity == lq->head) return true;
	return false;
}

bool insert(loop_queue** lq,int val)
{
	if(!isFull(*lq))
	{
		(*lq)->vals[((*lq)->tail)] = val;
		(*lq)->tail = ((*lq)->tail + 1) % (*lq)->capacity;
		
		return true;
	}
	return false;
}

bool pop(loop_queue** lq,int &val)
{
	if(!isEmpty(*lq))
	{
		val = (*lq)->vals[((*lq)->head)];
		(*lq)->head = ((*lq)->head + 1) % (*lq)->capacity;
		return true;
	}
	return false;
}

bool get_front(loop_queue* lq,int& val)
{
	if(!isEmpty(lq))
	{
		val = lq->vals[lq->head];
		return true;
	}
	return false;
}

int _tmain(int argc, _TCHAR* argv[])
{
	loop_queue* lq = create(5);
	for (int i = 1; i < 11; ++i)
	{
		cout<<insert(&lq,i)<<' ';
	}
	cout<<endl;

	for (int i = 1; i < 4; ++i)
	{
		int val;
		cout<<pop(&lq,val)<<' ';
	}
	cout<<endl;

	for (int i = 1; i < 11; ++i)
	{
		cout<<insert(&lq,i)<<' ';
	}
	cout<<endl;

	for (int i = 1; i < 11; ++i)
	{
		int val;
		cout<<pop(&lq,val)<<' ';
	}
	cout<<endl;
	cout<<lq->head<<' '<<lq->tail<<endl;
	for (int i = 1; i < 11; ++i)
	{
		cout<<insert(&lq,i)<<' ';
	}
	cout<<endl;
	return 0;
}

