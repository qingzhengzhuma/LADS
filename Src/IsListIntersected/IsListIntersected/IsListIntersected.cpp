// IsListIntersected.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
using namespace std;

struct list_node
{
	int data;
	list_node* next;
};

list_node* CreateList(int datas[],int n)
{
	if(n < 1) return NULL;
	list_node* head = new list_node;
	head->data = datas[0];
	head->next = NULL;
	list_node* p = head;
	for (int i = 1; i < n; ++i)
	{
		list_node* new_node = new list_node;
		new_node->data = datas[i];
		new_node->next = NULL;
		p->next = new_node;
		p = new_node;
	}
	return head;
}

void DisplayList(list_node* head)
{
	list_node* p = head;
	while(p)
	{
		cout<<p->data<<' ';
		p = p->next;
	}
	cout<<endl;
}

void FreeList(list_node* head)
{
	while(head)
	{
		list_node* p = head->next;
		delete head;
		head = p;
	}
}

bool IsInterseced(list_node* list1,list_node* list2,list_node** intersection_node)
{
	*intersection_node = NULL;
	if(list1 == NULL || list2 == NULL) return false;
	list_node* p1 = list1,*p2 = list2;
	
	int node_count1 = 1;
	while(p1->next)
	{
		++node_count1;
		p1 = p1->next;
	}

	int node_count2 = 1;
	while(p2->next)
	{
		++ node_count2;
		p2 = p2->next;
	}
	if(p1 != p2) return false;

	int D_value = 0;

	if(node_count1 >= node_count2)
	{
		p1 = list1;
		p2 = list2;
		D_value = node_count1 - node_count2;
	}
	else
	{
		p1 = list2;
		p2 = list1;
		D_value = node_count2 - node_count1;
	}

	for (int i = 0; i < D_value; ++i)
	{
		p1 = p1->next;
	}
	while(p1 != p2)
	{
		p1 = p1->next;
		p2 = p2->next;
	}

	*intersection_node = p1;

	return true;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int datas[] = {3,2,0,3,6,8,34,23,9,5,4};
	list_node* list1 = CreateList(datas,11);
	list_node* list2 = CreateList(datas,7);
	DisplayList(list1);
	DisplayList(list2);
	list_node* intersection_node = NULL;
	cout<<IsInterseced(list1,list2,&intersection_node)<<endl;
	list_node* list2_tail = list2;
	for (int i = 0; i < 6; ++i)
	{
		list2_tail = list2_tail->next;
	}
	//让第二个链表的最后一个节点的next指针指向第
	//一个链表的第二个节点，如此则两个链表相交
	list2_tail->next = list1->next->next;
	cout<<IsInterseced(list1,list2,&intersection_node)<<endl;
	cout<<intersection_node->data<<endl;
	return 0;
}

