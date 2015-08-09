#ifndef _VECTOR_H_
#define _VECTOR_H_

#include "../Utilites/type_traits.h"
#include <memory.h>

namespace MyDataStructure
{
	template<typename T>
	class Vector
	{
	public:
		typedef typename ParameterTrait<T>::ParameterType ParameterType;
		typedef T ValueType;
		typedef T* iterator;
		typedef const T* const_iterator;
	private:
		int capacity;
		int size_;
		T *vals;
	private:
		void copy(const Vector& v)
		{
			if (v.capacity != 0)
			{
				vals = new T[v.capacity];
				memcpy(vals, v.vals, v.capacity*sizeof(T));
			}
			else
			{
				vals = NULL;
			}
			capacity = v.capacity;
			size_ = v.size_;
		}
		void destroy()
		{
			capacity = size_ = 0;
			if (vals) delete[]vals;
			vals = NULL;
		}
		void forward_move(int start, int end,int targ)
		{
			if (start > end) return;
			if (targ >= start) return;
			while ( start <= end)
				vals[targ++] = vals[start++];
		}
	public:
		Vector() : capacity(0), size_(0), vals(NULL){};
		Vector(int capacity) : capacity(capacity), size_(0)
		{
			vals = new T[capacity];
			memset(vals, 0, capacity*sizeof(T));
		}
		iterator First()
		{
			if (size_ > 0) return vals;
			else return nullptr;
		}
		iterator Last()
		{
			if (size_ > 0) return &vals[size_ - 1];
			else return nullptr;
		}
		iterator End()
		{ 
			if (size_ > 0) return &vals[size_];
			else return nullptr; 
		}
		Vector(const Vector& v)
		{
			copy(v);
		}
		Vector& operator = (const Vector& v)
		{
			if (this != &v)
			{
				destroy();
				copy(v);
			}

			return *this;
		}
		void Resize(int capacity)
		{
			if (capacity <= 0) return;
			T* vs = new T[capacity];
			if (capacity <= this->capacity)
			{
				memcpy(vs, this->vals, capacity*sizeof(T));
			}
			else
			{
				memset(vs, 0, capacity*sizeof(T));
				memcpy(vs, this->vals, this->capacity*sizeof(T));
			}
			this->capacity = capacity;
			this->vals = vs;
			if (capacity < this->size_)
				size_ = capacity;
		}

		void PushBack(ParameterType val)
		{
			if (capacity == 0)
				Resize(2);
			else if (size_ >= capacity - 1)
				Resize(capacity * 2);
			vals[size_++] = val;
		}

		const T& operator [](int index) const
		{
			return vals[index];
		}
		T& operator[](int index)
		{
			return vals[index];
		}
		void Clear()
		{
			size_ = 0;
		}
		bool Empty()
		{
			return size_ == 0;
		}
		bool Null()
		{
			return capacity == 0;
		}
		int Size() const
		{
			return size_;
		}
		int Capacity() const { return capacity; }
		void Erase(int index)
		{
			if (index < 0 || index >= size_) return;
			forward_move(index + 1, --size_, index);
		}
		void Erase(int start, int end)
		{
			if (start < 0 || start >= size_) return;
			if (end < 0 || end >= size_) return;
			if (start > end) return;
			forward_move(end + 1, size_ - 1, start);
			size_ -= (end - start + 1);
		}
		int FindFirst(T val)
		{
			for (int i = 0; i < size_; ++i)
			{
				if (vals[i] == val) return i;
			}
			return -1;
		}

		int FindLast(T val)
		{
			for (int i = size_ - 1; i >= 0; --i)
			{
				if (vals[i] == val) return i;
			}
			return -1;
		}

		Vector<int> FindAll(T val)
		{
			Vector<int> v;
			for (int i = 0; i < size_; ++i)
			{
				if (vals[i] == val) v.push_back(i);
			}
			return v;
		}
	};
}


#endif