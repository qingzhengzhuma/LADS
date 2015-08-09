// WordCount.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct word_node
{
	char* str;
	int count;
	word_node* next;
};

struct list_head
{
	int count;
	word_node* next;
};

const int NHASH = 29989;
const int MULT = 31;

unsigned int my_hash(const char* str)
{
	const char* p = str;
	unsigned int h = 0;
	while(*p)
	{
		h = MULT*h + *p;
		++p;
	}
	return h % NHASH;
}

word_node* find(list_head* hash_list,const char* str)
{
	word_node* p = hash_list->next;
	while(p)
	{
		if(strcmp(str,p->str) == 0) return p;
		p = p->next;
	}
	return NULL;
}

void insert(list_head* hash_list,word_node* node)
{
	node->next = hash_list->next;
	hash_list->next = node;
	++hash_list->count;
}

int pre_process(const char* filename)
{
	ifstream input;
	input.open(filename);
	ofstream o;
	o.open("C:/Users/liaojian/Documents/result_no_digital.txt");
	string word;
	int n = 0;
	while(input>>word)
	{
		string s;
		const char* p = word.c_str();
		
		while(*p)
		{
			char c = *p;
			if(c <= 'z' && c >= 'a')
				s += c;
			else if(c <= 'Z' && c >= 'A')
			{
				s +=  c + 32;
			}
			++p;
		}
		if(s != "")
		{
			o<<s<<' ';
			++n;
		}
	}
	input.close();
	o.close();
	return n;
}

list_head* count(const char* filename,int &most_word_count)
{
	ifstream input;
	input.open(filename);
	string word;
	list_head* hash_list = new list_head[NHASH];
	memset(hash_list,0,NHASH*sizeof(list_head));
	most_word_count = 1;
	while(input>>word)
	{
		const char* wordptr = word.c_str();
		unsigned int h = my_hash(wordptr);
		word_node* node = find(&hash_list[h],wordptr);
		if(node)
		{
			++node->count;
			if(node->count > most_word_count)
				most_word_count = node->count;
		}
		else
		{
			node = new word_node;
			node->count = 1;
			node->str = new char[strlen(wordptr) + 1];
			strcpy(node->str,wordptr);
			insert(&hash_list[h],node);
		}
	}
	return hash_list;
}

void copy(word_node* dst_node,const word_node* src_node)
{
	dst_node->count = src_node->count;
	dst_node->str = new char[strlen(src_node->str) + 1];
	strcpy(dst_node->str,src_node->str);
}

void free_list(list_head *word_list,int list_count)
{
	for (int i = 0; i < list_count; ++i)
	{
		word_node* p = word_list[i].next;
		while(p)
		{
			word_node* q = p->next;
			delete p;
			p = q;
		}
	}
	delete []word_list;
	word_list = NULL;
}

list_head* sort(list_head* word_list,int list_count,int most_word_count)
{
	list_head* sorted_word_list = new list_head[most_word_count];
	memset(sorted_word_list,0,most_word_count*sizeof(list_head));
	for (int i = 0; i < list_count; ++i)
	{
		word_node* p = word_list[i].next;
		while(p)
		{
			word_node* node = new word_node;
			copy(node,p);
			insert(&sorted_word_list[most_word_count - p->count],node);
			p = p->next;
		}
	}
	return sorted_word_list;
}



int _tmain(int argc, _TCHAR* argv[])
{
	char* src_file_name = "C:/Users/liaojian/Documents/result_no_digital.txt";
	char* dst_file_name = "C:/Users/liaojian/Documents/count_result_no_digital_sorted.txt";
	ofstream o;
	o.open(dst_file_name);
	int most_word_count;
	list_head* hash_list = count(src_file_name,most_word_count);
	list_head* sorted_word_list = sort(hash_list,NHASH,most_word_count);
	for (int i = 0; i < most_word_count; ++i)
	{
		word_node* p = sorted_word_list[i].next;
		while(p)
		{
			o<<p->str<<' '<<p->count<<endl;
			p = p->next;
		}
	}
	free_list(hash_list,NHASH);
	free_list(sorted_word_list,most_word_count);
	return 0;
}

