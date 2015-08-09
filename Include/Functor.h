#ifndef _FUNCTOR_H_
#define _FUNCTOR_H_
#include "../Utilites/type_traits.h"
namespace MyDataStructure
{
	
	template<typename T>
	struct less
	{
		typedef typename ParameterTrait<T>::ParameterType ParameterType;
		bool operator ()(const ParameterType op1, const ParameterType op2)
		{
			return op1 < op2;
		}
	};

	template<typename T>
	struct greater
	{
		typedef typename ParameterTrait<T>::ParameterType ParameterType;
		bool operator ()(const ParameterType op1, const ParameterType op2)
		{
			return op1 > op2;
		}
	};
}

#endif