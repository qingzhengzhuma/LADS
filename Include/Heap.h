#ifndef _HEAP_H_
#define _HEAP_H_

#include "../include/Functor.h"
#include "../Utilites/type_traits.h"
#include "Vector.h"
namespace MyDataStructure
{
	//�����ݽṹ��Ĭ��Ϊ��С�ѣ���Ҫ��
	//��ѣ�ֻ��ָ���Ⱥ���Ϊ���ڱȽ�
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
		//ʹ��Vector��֧�ֶ�̬����
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
		//�����һ��Ԫ�ظ��ǵ���һ��Ԫ��
		values[0] = values[size - 1];
		//ɾ�����һ��Ԫ��
		values.Erase(size - 1);
		--size;
		//�Ե�һ��Ԫ��ִ�����˲���
		sift_down(0,size - 1);
	}
	
	template<typename ValueType, typename Compare>
	void Heap<ValueType, Compare>::copy(const Vector<ValueType>& values)
	{
		this->values = values;
	}

	//����������ݣ�������Ҫ����ռ�õ��ڴ�
	template<typename ValueType, typename Compare>
	void Heap<ValueType, Compare>::clear()
	{
		values.Clear();
	}
	
	//����(������Ϊ��������ĳ��Ԫ��x��ʼ���ֱ������������Һ��ӱȽϣ�
	//���С����������һ������ô�Ͱ���������С��һ������x��Ȼ�����x���ŵ���
	//֮ǰ��������СԪ�����ڵ�λ���ϣ��ظ�����Ĺ��̣�ֱ��x���ڻ��������
	//���Һ��ӻ򵽴��˶ѵ�ĩβ��Ȼ���x�ŵ����¿ճ�����λ����
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
	
	//����(������Ϊ��),��ĳ��Ԫ��x��ʼ�������ȸ��ڵ㻹��
	//��ô�ͰѸ��ڵ㸲�ǵ�x��λ���ϣ�Ȼ�����x���ŵ����ڵ��λ�ã�
	//�ظ�����Ĺ��̣�ֱ��x���ڻ�����������Һ���
	//�򵽴��˶Ѷ���Ȼ���x�ŵ����¿ճ�����λ����
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

	//�����ѣ�������Ϊ�������Ӷѵ��м�λ�ã�����Ԫ��
	//��ż����ʱ��ȡ����λ����Ϊ����ʱ��ȡ��λ����ǰһ����
	//��ʼ��ǰ��ÿ��Ԫ��ִ�����˲������м�λ�ú��Ԫ��һ����
	//ǰ��Ԫ�صĺ��ӣ����Ժ���������н�С��Ԫ��һ���ᱻ��
	//�����ģ�ͬʱ�ϴ��Ԫ�ػᱻ�·�
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