#ifndef _TYPE_TRAITS_H_
#define _TYPE_TRAITS_H_

namespace MyDataStructure
{
	template<typename T>
	class ParameterTrait
	{
	private:
		template<typename U>
		struct __ParaTrait
		{
			typedef U& ParameterType;
		};

		template<typename U>
		struct __ParaTrait<U*>
		{
			typedef U* ParameterType;
		};

		template<>
		struct __ParaTrait<char>
		{
			typedef char ParameterType;
		};

		template<>
		struct __ParaTrait<unsigned char>
		{
			typedef unsigned char ParameterType;
		};

		template<>
		struct __ParaTrait<int>
		{
			typedef int ParameterType;
		};

		template<>
		struct __ParaTrait<unsigned int>
		{
			typedef unsigned int ParameterType;
		};
		template<>
		struct __ParaTrait<bool>
		{
			typedef bool ParameterType;
		};

	public:
		typedef typename __ParaTrait<T>::ParameterType ParameterType;
	};
}

#endif