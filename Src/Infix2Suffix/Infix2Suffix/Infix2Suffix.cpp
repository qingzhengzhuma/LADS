// Infix2Suffix.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <conio.h>

#include <iostream>
#include <stack>

using namespace std;

const int expr_length = 1025;
char expr_buf[expr_length];

enum char_category
{
	illigal,
	a_number,
	an_operator,
	ignored
};

char opertors[] = 
{
	'(',
	'*',
	'/',
	'+',
	'-',
	')'
};

bool is_number(char c)
{
	if(c >= '0' && c <= '9') return true;
	return false;
}

bool is_operator(char c)
{
	int count = sizeof opertors;
	bool res = false;
	for (int i = 0; i < count; ++i)
		if(c == opertors[i]) res = true;
	return res;
}

bool is_ignored(char c)
{
	if(c == ' ') return true;
	return false;
}

char_category get_char_category(char c)
{
	if(is_number(c)) return a_number;
	if(is_operator(c)) return an_operator;
	if(is_ignored(c)) return ignored;
	return illigal;
}

bool get_input()
{
	char c;
	int i = 0;
	memset(expr_buf,0,expr_length*sizeof(char));
	while((c = _getch()) != -1 && i < expr_length)
	{
		if(c == 13)
		{
			cout<<endl;
			return true;
		}
		else if(c == 8 && i > 0)
		{
			expr_buf[--i] = '\0';
			system("cls");
			cout<<expr_buf;
			continue;
		}
		char_category cc = get_char_category(c);
		if(cc == illigal || cc == ignored)
		{
			cout<<'\a';
			continue;
		}
		else if(cc == a_number || cc == an_operator)
		{
			expr_buf[i++] = c;
		}
		cout<<c;
		if(i == 1024) return true;
	}
	return false;
}


int _tmain(int argc, _TCHAR* argv[])
{
	if(get_input())
	{
		cout<<expr_buf<<endl;
		cout<<strlen(expr_buf)<<endl;
	}
	else
		cout<<"Illegal Input!"<<endl;
	return 0;
}

