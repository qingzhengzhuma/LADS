#ifndef _FUNC_H_
#define _FUNC_H_

#include "Vector.h"
using namespace MyDataStructure;

template<typename T1,typename ... Types>
class Func
{
private:
	typedef T1 (*function)(Types ...paras);
	typedef function func;
	Vector<func> funcs;
public:
	Func& operator = (const func f)
	{
		funcs.Clear();
		return (*this += f);
	}

	Func& operator += (const func f)
	{
		funcs.PushBack(f);
		return *this;
	}

	Func& operator -= (const func f)
	{
		funcs.Erase(funcs.FindLast(f));
		return *this;
	}

	Vector<T1> operator()(Types ...paras)
	{
		Vector<T1> v;
		int count = funcs.Size();
		for (int i = 0; i < count; i++)
		{
			v.PushBack(funcs[i](paras...));
		}
		return v;
	}
};


#endif