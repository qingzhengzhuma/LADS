#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "..\Utilites\type_traits.h"

namespace MyDataStructure
{
	template<typename T>
	class BiDirectionNode
	{
	private:
		typedef typename ParameterTrait<T>::ParameterType ParameterType;
	public:
		BiDirectionNode(const ParameterType value) : value(value),next(nullptr),pre(nullptr) {}
		BiDirectionNode(const BiDirectionNode& n)
		{
			_copy(n);
		}

		BiDirectionNode& operator = (const BiDirectionNode& n)
		{
			_copy(n);
			return *this;
		}
		T Value() const { return value; }
		T& Value() { return value; }
		T* Next() { return next; }
	public:
		void _copy(const BiDirectionNode& n)
		{
			value = n.value;
			next = n.next;
			pre = n.pre;
		}
		T value;
		BiDirectionNode* pre;
		BiDirectionNode* next;
	};

	template<typename T>
	class List
	{
	private:
		typedef typename BiDirectionNode<T> NodeType;
		typedef typename ParameterTrait<T>::ParameterType ParameterType;
	public:
		List() : size(0), head(nullptr),tail(nullptr){}
		List(const List& d){ _copy(d); }
		List& operator=(const List& d){ _destroy(); _copy(d); return *this; }
		~List(){ _destroy(); }
		void Clear() { _destroy(); }
		const int Size() { return size; }
		bool Empty(){ return size == 0; }
		void Push(const ParameterType value)
		{
			NodeType* n = new NodeType(value);
			_push(n);
		}
		void Insert(const ParameterType value)
		{
			NodeType* n = new NodeType(value);
			_insert(n);
		}
		bool Pop(T& value)
		{
			if (size == 0)
				return false;
			value = head->value;
			NodeType* p = head;
			if (size == 1)
			{
				head = tail = nullptr;
			}
			else
			{
				head = head->next;
				head->pre = nullptr;
			}
			--size;
			delete p;
			return true;
		}
		bool Eject(T& value)
		{
			if (size == 0)
				return false;
			value = tail->value;
			NodeType* p = tail;
			if (size == 1)
			{
				head = tail = nullptr;
			}
			else
			{
				tail = tail->pre;
				tail->next = nullptr;
			}
			
			--size;
			delete p;
			return true;
		}
	private:
		void _push( NodeType* n)
		{
			if (size == 0)
			{
				head = n;
				head->next = nullptr;
				head->pre = nullptr;
				tail = head;
			}
			else
			{
				n->next = head;
				n->pre = nullptr;
				head->pre = n;
				head = n;
			}
			++size;
		}
		void _insert( NodeType* n)
		{
			if (size == 0)
			{
				head = n;
				head->next = nullptr;
				head->pre = nullptr;
				tail = head;
			}
			else
			{
				tail->next = n;
				n->pre = tail;
				n->next = nullptr;
				tail = n;
			}
			++size;
		}
		void _copy(const List& d)
		{
			NodeType* node = d.head;
			while (node)
			{
				NodeType* newNode = new NodeType(*node);
				_insert(newNode);
				node = node->next;
			}
		}
		void _destroy()
		{
			NodeType* node = head;
			while (node)
			{
				NodeType* p = node->next;
				delete node;
				node = p;
			}
			head = tail = nullptr;
			size = 0;
		}
	private:
		int size;
		NodeType* head;
		NodeType* tail;
	};
}

#endif