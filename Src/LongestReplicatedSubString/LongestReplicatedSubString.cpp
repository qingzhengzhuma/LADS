// LongestReplicatedSubString.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct letter_node
{
	char letter;
	float probability;
	letter_node *next;
};

struct prefix_node
{
	char prefix[4];
	int letter_count;
	letter_node * letter;
};

void get_prefix_counts(vector<int> &prefix_counts,vector<char*> &suffix_array,int order)
{
	prefix_counts.clear();
	int suffix_count = suffix_array.size();
	int current_prefix_count = 0;
	for (int i = 0; i < suffix_count - 1; ++i)
	{
		char* p = suffix_array[i],*q = suffix_array[i + 1];
		int j = 0;
		for (; j < order; ++j)
		{
			if(*p != *q) break;
		}
		if( j < order)
		{
			prefix_counts.push_back(current_prefix_count);
			current_prefix_count = 0;
		}
		else
		{
			++current_prefix_count;
		}
	}
}

void insert(prefix_node &prefix,letter_node *lnode)
{
	if(prefix.letter_count == 0 || prefix.letter->probability < lnode->probability)
	{
		lnode->next = prefix.letter;
		prefix.letter = lnode;
		++prefix.letter_count;
		return;
	}
	letter_node *q = prefix.letter,*p = q->next;
	while(p && p->probability >= lnode->probability)
	{
		q = p;
		p = p->next;
	}
	lnode->next = q->next;
	q->next = lnode;
	++prefix.letter_count;
}

prefix_node* create_prefix_list(vector<char*> &suffix_array,vector<int> prefix_counts,int order)
{
	prefix_counts.clear();
	get_prefix_counts(prefix_counts,suffix_array,order);
	int total_prefix_count = prefix_counts.size();
	prefix_node* prefix_list = new prefix_node[total_prefix_count];
	memset(prefix_list,0,total_prefix_count*sizeof(prefix_node));
	int j = 0;
	int fre[128];
	for (int i = 0; i < total_prefix_count; ++i)
	{
		memset(fre,0,127*sizeof(int));
		int count = prefix_counts[i];
		for (int k = 0; k < count; ++k)
		{
			++fre[suffix_array[j][2]];
			++j;
		}
		for (int k = 0; k < 128; ++k)
		{
			if(fre[k] == 0) continue;
			float prob = 1.0f*fre[k] / count;
			letter_node *node = new letter_node;
			node->letter = k;
			node->probability = prob;
			insert(prefix_list[i],node);
		}
	}
	return prefix_list;
}

int partition(vector<char*> &suffix_array,int start,int end)
{
	char * pivot = suffix_array[start];
	while(start < end)
	{
		while(start < end && strcmp(suffix_array[end],pivot) >= 0) --end;
		suffix_array[start] = suffix_array[end];
		while(start < end && strcmp(suffix_array[start],pivot) <= 0) ++start;
		suffix_array[end] = suffix_array[start];	
	}
	suffix_array[start] = pivot;
	return start;
}

void sort(vector<char*> &suffix_array,int start,int end)
{
	if(start < end)
	{
		int pivot = partition(suffix_array,start,end);
		sort(suffix_array,start,pivot - 1);
		sort(suffix_array,pivot + 1,end);
	}
}

void sort(vector<char*> &suffix_array)
{
	int length = suffix_array.size();
	sort(suffix_array,0,length - 1);
}

void init(const char* filename,string &text,vector<char*> &suffix_array)
{
	text.clear();
	suffix_array.clear();
	FILE* fp = fopen(filename,"r");
	char c;
	while((c = fgetc(fp)) != EOF)
	{
		text += c;
	}
	fclose(fp);
	int length = text.length();
	suffix_array.resize(length);
	for (int i = 0; i < length; ++i)
	{
		suffix_array[i] = &text[i];
	}
}

int wordcmp(const char * word1,const char * word2)
{
	char* p = (char*)word1,*q = (char*)word2;
	int replicated_prefix_count = 0;
	while(*p && *q && *p == *q)
	{
		++replicated_prefix_count;
		++p;
		++q;
	}
	return replicated_prefix_count;
}



char* find_longest_replicated_prefix(vector<char*> &suffix_array)
{
	int count = 0,fix_count = suffix_array.size();
	int index = -1;
	char * res = NULL;
	for (int i = 1; i < fix_count; ++i)
	{
		int n = wordcmp(suffix_array[i - 1],suffix_array[i]);
		if(n > count)
		{
			count = n;
			index = i;
		}
	}
	if(index != -1)
	{
		res = new char[count + 1];
		memset(res,0,(count + 1)*sizeof(char));
		memcpy(res,suffix_array[index],count);
	}
	return res;
}

int _tmain(int argc, _TCHAR* argv[])
{
	string s = "C:/Users/liaojian/Documents/The Homer_1.txt";
	const char* filename = s.c_str();
	string text;
	vector<char*> suffix_array;
	init(filename,text,suffix_array);
	sort(suffix_array);
	char * res = find_longest_replicated_prefix(suffix_array);
	cout<<res<<endl;
	/*string s1 = "and with the gleam of armour. Then Jove spread panic among my men, and they would no longer face the enemy, for they found themselves surrounded. The Egyptians killed many of us, and took the rest alive to do forced labour for";
	string s2 = "whose sake so many of the Achaeans have died at Troy, far from their homes? Go about at once among the host, and speak fairly to them, man by man,that they draw not their ships into the sea.";
	cout<<s1.length()<<" "<<s2.length()<<endl;*/
	return 0;
}

