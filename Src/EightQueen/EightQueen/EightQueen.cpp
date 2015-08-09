// EightQueen.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <time.h>

using namespace std;


const int candidate_pos = 0;
const int legal_pos = 1;

struct chessboard
{
	int size;
	int *board;
};

chessboard* create(int size)
{
	chessboard* cb = new chessboard;
	cb->size = size;
	cb->board = new int[size*size];
	memset(cb->board,0,size*size*sizeof(int));
	return cb;
}

void print(chessboard* cb)
{
	int size = cb->size;
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
			cout<<cb->board[i*size + j]<<' ';
		cout<<endl;
	}
	cout<<endl;
}

bool check(chessboard* cb,int row,int col)
{
	int size = cb->size;
	int* board = cb->board;

	//�����
	int* p = &board[col];
	for (int i = 0; i < row; ++i)
	{
		if(*p) return false;
		p += size;
	}

	//�����������½��ĶԽ���
	for (int i = row - 1,j = col - 1; i >= 0 && j >= 0; --i,--j)
	{
		if(board[i*size + j]) return false;
	}

	//�����������½��ĶԽ���
	for (int i = row - 1,j = col + 1; i >= 0 && j < size; --i,++j)
	{
		if(board[i*size + j]) return false;
	}
	return true;
}

void _solve(chessboard** cb,int i,int j,int &count)
{
	//���л��е�ά���ϣ�����ά���˾�ͷ����������������������һ��
	if(i >= (*cb)->size || j >= (*cb)->size) return;
	int size = (*cb)->size;
	int* board = (*cb)->board;

	//�ҵ�һ�����Է��ûʺ��λ�ú�
	if(check(*cb,i,j))
	{
		//����λ����Ϊ1����ʾ������һ���ʺ�
		board[i*size + j] = legal_pos;

		//��������һ�У��Ǳ�ʾ�õ���һ�����
		if(i == size - 1)
		{
			++count;
			//print(*cb);
		}
		//��������һ��������һ���ʺ��λ��
		else _solve(cb,i + 1,0,count);

		//���ܺ���������ҵ������⣬����Ҫ���ڱ��и�
		//���ҵ��ʺ�Ų�������ݹ��̲ſ�������ȷ��
		board[i*size + j] = candidate_pos;
	}
	//����ÿһ���е�jλ�ã���������һ�����Ի򲻿��Է���
	//�ʺ��λ�ã���Ҫ��������������������еĽ�
	_solve(cb,i,j + 1,count);
}

int solve_eightqueen(int size)
{
	int count = 0;
	chessboard* cb = create(size);
	//�ӵ�һ��λ�ÿ�ʼ����
	_solve(&cb,0,0,count);
	return count;
}


int _tmain(int argc, _TCHAR* argv[])
{
	/*cout<<"=============1============"<<endl;
	int count = solve_eightqueen(1);
	cout<<"Total:"<<count<<endl;

	cout<<"=============2============"<<endl;
	count = solve_eightqueen(2);
	cout<<"Total:"<<count<<endl;

	cout<<"=============3============"<<endl;
	count = solve_eightqueen(3);
	cout<<"Total:"<<count<<endl;

	cout<<"=============4============"<<endl;
	count = solve_eightqueen(4);
	cout<<"Total:"<<count<<endl;*/

	cout<<"=============12============"<<endl;
	clock_t t1 = clock();
	int count = solve_eightqueen(12);
	cout<<"Total:"<<count<<endl;
	cout<<"TIME:"<<(clock() - t1) / 1000.0f<<'s'<<endl;
	return 0;
}

