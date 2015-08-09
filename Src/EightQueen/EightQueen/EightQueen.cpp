// EightQueen.cpp : 定义控制台应用程序的入口点。
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

	//检查列
	int* p = &board[col];
	for (int i = 0; i < row; ++i)
	{
		if(*p) return false;
		p += size;
	}

	//检查从左往右下降的对角线
	for (int i = row - 1,j = col - 1; i >= 0 && j >= 0; --i,--j)
	{
		if(board[i*size + j]) return false;
	}

	//检查从右往左下降的对角线
	for (int i = row - 1,j = col + 1; i >= 0 && j < size; --i,++j)
	{
		if(board[i*size + j]) return false;
	}
	return true;
}

void _solve(chessboard** cb,int i,int j,int &count)
{
	//在行或列的维度上，任意维到了尽头，则本行搜索结束，返回上一行
	if(i >= (*cb)->size || j >= (*cb)->size) return;
	int size = (*cb)->size;
	int* board = (*cb)->board;

	//找到一个可以放置皇后的位置后
	if(check(*cb,i,j))
	{
		//将该位置设为1，表示放置了一个皇后
		board[i*size + j] = legal_pos;

		//如果是最后一行，那表示得到了一个解喽
		if(i == size - 1)
		{
			++count;
			//print(*cb);
		}
		//否则往下一行搜索下一个皇后的位置
		else _solve(cb,i + 1,0,count);

		//不管后面的搜索找到几个解，都需要把在本行刚
		//才找到皇后挪开，回溯过程才可能是正确的
		board[i*size + j] = candidate_pos;
	}
	//对于每一行中的j位置，不管它是一个可以或不可以放置
	//皇后的位置，都要继续往后搜索，以穷尽所有的解
	_solve(cb,i,j + 1,count);
}

int solve_eightqueen(int size)
{
	int count = 0;
	chessboard* cb = create(size);
	//从第一个位置开始搜索
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

