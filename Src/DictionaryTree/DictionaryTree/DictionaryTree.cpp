// DictionaryTree.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

struct letter_node
{
	bool IsTerminate;
	char c;
	letter_node* sib;
	letter_node* next;
};

struct dict_tree
{
	int word_count;
	letter_node* head;
};

bool IsLegalWord(const char* word)
{
	int length = strlen(word);
	const char* p = word;
	for (int i = 0; i < length; ++i)
	{
		char c = *p++;
		if(!(c <= 'z' && c >= 'a' || c <= 'Z' && c >= 'A')) return false;
	}
	return true;
}

letter_node* create_letter(const char c)
{
	letter_node *node = new letter_node;
	node->c = c;
	node->IsTerminate = false;
	node->sib = NULL;
	node->next = NULL;
	return node;
}

void _treverse(letter_node* letter,string &prefix)
{
	if(letter == NULL) return;
	string l = prefix + letter->c; 
	if(letter->IsTerminate) cout<<l<<endl;
	if(letter->next)
	{
		_treverse(letter->next,l);
	}
	if(letter->sib) _treverse(letter->sib,prefix);
}

void treverse(dict_tree* dict)
{
	string s = "";
	_treverse(dict->head,s);
}



letter_node* add_letter(letter_node** head,char c)
{
	letter_node *p = *head;
	if(p == NULL)
	{
		p = create_letter(c);
		*head = p;
		return p;
	}
	letter_node *res = p;
	while(res->sib)
	{
		if(res->c == c) return res;
		res = res->sib;
	}
	res->sib = create_letter(c);
	return res->sib;
}

const letter_node* find_letter(const letter_node* head,char c)
{
	const letter_node *res = head;
	while(res)
	{
		if(res->c == c) return res;
		res = res->sib;
	}
	return NULL;
}

bool IsWordContained(const dict_tree* dict,const char* word)
{
	const char* p = word;
	const letter_node *head = dict->head;
	const letter_node * node;
	while(*p)
	{
		node = find_letter(head,*p);
		if(!node) return false;
		head = node->next;
		++p;
	}
	if(node->IsTerminate)
		return true;
	return false;
}

bool insert_word(dict_tree **dict,const char * word)
{
	if(!IsLegalWord(word)) return false;
	const char* c = word;
	letter_node* letter = add_letter(&((*dict)->head),*c);
	while(*(++c))
	{
		letter = add_letter(&(letter->next),*c);
	}
	letter->IsTerminate = true;
	++((*dict)->word_count);
	return true;
}

dict_tree* create_dict_tree(const char* filename)
{
	dict_tree* root = new dict_tree;
	root->head = NULL;
	root->word_count = 0;
	ifstream input;
	input.open(filename);
	string word;
	while(input>>word)
	{
		insert_word(&root,word.c_str());
	}
	return root;
}


int _tmain(int argc, _TCHAR* argv[])
{
	const char* filename = "F:/program/DictionaryTree/Debug/test.txt";
	dict_tree* dict = create_dict_tree(filename);
	treverse(dict);
	cout<<dict->word_count<<endl;
	cout<<IsWordContained(dict,"tumors")<<endl;
	cout<<IsWordContained(dict,"tumor")<<endl;
	return 0;
}

