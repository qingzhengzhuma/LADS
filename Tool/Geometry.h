#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_

namespace MyTools
{
	template<typename T>
	class Point
	{
	public:
		Point() :x(0), y(0){};
		Point(T x, T y) : x(x), y(y){}
		~Point(){};
	public:
		T x;
		T y;
	};
}

#endif