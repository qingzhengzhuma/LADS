#ifndef _HEAP_H_
#define _HEAP_H_

#include "../include/Functor.h"
#include "../Utilites/type_traits.h"
#include "Vector.h"
namespace MyDataStructure
{
	//堆数据结构，默认为最小堆，需要最
	//大堆，只需指定比函数为大于比较
	template<typename ValueType,typename Compare = less<ValueType>>
	class Heap
	{
	public:
		typedef typename ParameterTrait<ValueType>::ParameterType ParameterType;
		typedef typename Heap<ValueType> self;
	public:
		Heap(){};
		Heap(int capacity);
		Heap(ValueType values[], int count);
		Heap(const Heap& rhs);
		self& operator = (const Heap& rhs);
		~Heap(){}
		void Insert(const ParameterType value);
		bool GetTop(ValueType& top);
		void RemoveTop();
		void Clear(){ values.Clear(); }
		int Size(){ return values.Size(); }
		int Capacity(){ return values.Capacity(); }
	private:
		void copy(const Vector<ValueType>& values);
		void clear();
		void sift_down(int start,int end);
		void sift_up(int start);
		void build_heap();
	private:
		//使用Vector以支持动态扩容
		Vector<ValueType> values;
		Compare comp;
	};

	template<typename ValueType, typename Compare>
	Heap<ValueType, Compare>::Heap(int capacity)
	{
		values.Resize(capacity);
	}

	template<typename ValueType, typename Compare>
	Heap<ValueType, Compare>::Heap(ValueType values[], int count)
	{
		for (int i = 0; i < count; ++i)
		{
			this->values.PushBack(values[i]);
		}
		build_heap();
	}

	template<typename ValueType,typename Compare>
	Heap<ValueType, Compare>::Heap(const Heap& rhs)
	{
		clear();
		copy(rhs.values);
	}

	template<typename ValueType, typename Compare>
	typename Heap<ValueType,Compare>::self&
	Heap<ValueType, Compare>
	::operator=(const Heap<ValueType, Compare>& rhs)
	{
		clear();
		copy(rhs.values);
		return *this;
	}

	template<typename ValueType, typename Compare>
	void Heap<ValueType, Compare>::Insert(const ParameterType value)
	{
		values.PushBack(value);
		sift_up(values.Size() - 1);
	}

	template<typename ValueType, typename Compare>
	bool Heap<ValueType, Compare>::GetTop(ValueType& top)
	{
		if(values.Size() <= 0) return false;
		else
		{
			top = values[0];
			return true;
		}
	}

	template<typename ValueType, typename Compare>
	void Heap<ValueType, Compare>::RemoveTop()
	{
		int size = values.Size();
		if (size <= 0) return;
		ValueType temp = values[0];
		//将最后一个元素覆盖到第一个元素
		values[0] = values[size - 1];
		//删除最后一个元素
		values.Erase(size - 1);
		--size;
		//对第一个元素执行下滤操作
		sift_down(0,size - 1);
	}
	
	template<typename ValueType, typename Compare>
	void Heap<ValueType, Compare>::copy(const Vector<ValueType>& values)
	{
		this->values = values;
	}

	//清除堆中数据，并不需要销毁占用的内存
	template<typename ValueType, typename Compare>
	void Heap<ValueType, Compare>::clear()
	{
		values.Clear();
	}
	
	//下滤(以最大堆为例），从某个元素x开始，分别将其与他的左右孩子比较，
	//如果小于其中任意一个，那么就把三者中最小的一个覆盖x，然后假设x被放到了
	//之前三者中最小元素所在的位置上，重复上面的过程，直到x大于或等于他的
	//左右孩子或到达了堆的末尾，然后把x放到最新空出来的位置上
	template<typename ValueType, typename Compare>
	void Heap<ValueType, Compare>::sift_down(int start,int end)
	{
		int i = start, j = 2 * i + 1;
		ValueType temp = values[i];
		while ( j <= end)
		{
			if (j < end && comp(values[j + 1], values[j])) ++j;
			if (!comp(values[j], temp)) break;
			else
			{
				values[i] = values[j];
				i = j;
				j = 2 * i + 1;
			}
		}
		values[i] = temp;
	}
	
	//上滤(以最大堆为例),从某个元素x开始，如果其比父节点还大，
	//那么就把父节点覆盖到x的位置上，然后假设x被放到父节点的位置，
	//重复上面的过程，直到x大于或等于他的左右孩子
	//或到达了堆顶，然后把x放到最新空出来的位置上
	template<typename ValueType, typename Compare>
	void Heap<ValueType, Compare>::sift_up(int start)
	{
		int j = start,i = (j - 1) / 2;
		ValueType temp = values[j];
		while (j > 0)
		{
			if (!comp(temp,values[i])) break;
			else
			{
				values[j] = values[i];
				j = i;
				i = (j - 1) / 2;
			}
		}
		values[j] = temp;
	}

	//建立堆（以最大堆为例），从堆的中间位置（堆中元素
	//有偶数个时，取下中位数，为基数时，取中位数的前一个）
	//开始向前对每个元素执行下滤操作。中间位置后的元素一定是
	//前面元素的孩子，所以后半段中如果有较小的元素一定会被虑
	//上来的，同时较大的元素会被下放
	template<typename ValueType, typename Compare>
	void Heap<ValueType, Compare>::build_heap()
	{
		int end = values.Size() - 1;
		for (int i = (end - 1) / 2; i >= 0; --i)
		{
			sift_down(i, end);
		}
	}
}

#endif