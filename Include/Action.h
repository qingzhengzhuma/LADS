#ifndef _ACTION_H_
#define _ACTION_H_

#include "../include/Vector.h"
using namespace MyDataStructure;

template <typename ... Types>
class Action
{
private:
	typedef void(*function)(Types...paras);
	typedef function func;
	Vector<func> funcs;
public:
	Action& operator = (const func f)
	{
		funcs.Clear();
		return (*this += f);
	}

	Action& operator += (const func f)
	{
		funcs.PushBack(f);
		return *this;
	}

	Action& operator -= (const func f)
	{
		funcs.Erase(funcs.FindLast(f));
		return *this;
	}

	void operator()(Types ...paras)
	{
		int count = funcs.Size();
		for (int i = 0; i < count; i++)
		{
			funcs[i](paras...);
		}
	}
};

#endif