#ifndef _SEARCH_TREE_H_
#define _SEARCH_TREE_H_

#include "../Utilites/type_traits.h"
#include "Functor.h"
#include "BinaryNodeBase.h"
#include "SearchTreeIteratorBase.h"

namespace MyDataStructure
{
	//����Ľڵ���
	template<typename ValueType>
	struct BinaryNode : public BinaryNodeBase
	{
		typedef BinaryNode<ValueType>* LinkType;
		ValueType value;
	};


	
	//�����Ĳ�����������
	template<typename Value,typename Ref,typename Ptr>
	struct SearchTreeIterator : public SearchTreeIteratorBase
	{
		typedef Value ValueType;
		typedef Ref reference;
		typedef Ptr pointer;
		typedef SearchTreeIterator<Value, Value&, Value*> iterator;
		typedef SearchTreeIterator<Value, const Value&, Value*> const_iterator;
		typedef SearchTreeIterator<Value, Value&, Value*> self;
		typedef BinaryNodeBase* LinkType;
		typedef BinaryNode<Value>* NodePtr;

		SearchTreeIterator() { node = nullptr; }
		SearchTreeIterator(LinkType x) { node = x; }
		SearchTreeIterator(const iterator& it) { node = it.node; }
		self& operator =(const iterator& it) { node = it.node; return *this; }

		//ģ��ָ����Ϊ����������һ������ָ��
		reference operator *(){ return NodePtr(node)->value; }
		pointer operator ->() { return &(operator*()); }

		self& operator ++()
		{
			Increament();
			return *this;
		}

		self operator ++(int)
		{
			self tmp = *this;
			Increament();
			return tmp;
		}

		self& operator --()
		{
			Decreament();
			return *this;
		}

		self operator --(int)
		{
			self tmp = *this;
			Decreament();
			return tmp;
		}
	};

	template < typename T, typename Compare = less<T>>
	class SearchTree
	{
	public:
		typedef typename ParameterTrait<T>::ParameterType ParameterType;
		typedef typename BinaryNode<T> NodeType;
		typedef typename BinaryNode<T>* NodePtr;
		typedef typename BinaryNode<T>::BasePtr BasePtr;
		typedef typename SearchTreeIterator<T, T&, T*>::iterator iterator;
	public:

		//�����ַ�ʽ����һ�ò�������
		//  1������һ�ſ�����
		//  2������һ���Ѿ����ڵ���
		SearchTree() : size(0),head(nullptr){}
		SearchTree(const SearchTree& st)
		{
			copy(st);
		}
		SearchTree& operator = (const SearchTree& st)
		{
			if (&st != this)
			{
				Clear();
			    copy(st);
			}
			return *this;
		}
		~SearchTree(){ Clear(); }
		const int Size(){ return size; }
		void Clear()
		{
			_destroy(head);
			head = nullptr;
			size = 0;
		}

		//��������ظ�ֵ�ķ����������棩
		void Insert(T values[], int count)
		{
			for (int i = 0; i < count; ++i)
			{
				Insert(values[i]);
			}
		}

		//��������ظ�ֵ�ķ���
		void Insert(const ParameterType value)
		{
			//q��ʾ������½ڵ�ĸ��ڵ�
			BasePtr q = find_position_for_insert(value);
			//qΪnullptr�����ǿյģ����Թ���ͷ���
			if (q == nullptr)
			{
				create_head(value);
			}
			//���򣬲���ͺ���
			else
			{
				NodePtr node = create_node(value);
				insert(&q, node);
			}
		}

		//����������ظ�ֵ�ķ����������棩
		void UniqueInsert(T values[], int count)
		{
			for (int i = 0; i < count; ++i)
			{
				UniqueInsert(values[i]);
			}
		}
		//����������ظ�ֵ�ķ���
		void UniqueInsert(const ParameterType value)
		{
			//qͬInsert�У�ͨ��p����֪�������Ƿ�
			//�Ѿ�����ͬ����ֵ��
			BasePtr q = nullptr;
			BasePtr p = find_first(head,value, &q);
			if (q == nullptr)
			{
				create_head(value);
			}
			else
			{
				//p��Ϊ�գ���������ظ�ֵ������ʲôҲ������
				if (p != nullptr) return;
				NodePtr node = create_node(value);
				insert(&q, node);
			}
		}

		iterator FindFirst(const ParameterType value)
		{
			BasePtr temp = nullptr;
			return iterator(find_first(head,value,&temp));
		}

		iterator FindLast(const ParameterType value)
		{
			BasePtr temp = nullptr;
			return iterator(find_last(head, value, &temp));
		}

		//������ɾ��һ���ڵ�
		void Erase(iterator& it)
		{
			erase(it.node);
		}

		//������ɾ��һ���ڵ�
		void Erase(const ParameterType value)
		{
			Erase(FindFirst(value));
		}

		//�������е�Ԫ��������ģ������������˵Ľڵ�
		iterator First()
		{
			BasePtr first = nullptr;
			if (head) first = head->minimum();
			return iterator(first);
		}
		//�������е�Ԫ��������ģ�����������Ҷ˵Ľڵ�
		iterator Last()
		{
			BasePtr last = nullptr;
			if (head) last = head->maximum();
			return iterator(last);
		}

		//nullptrָʾ���˾�ͷ��
		iterator End()
		{
			return iterator(nullptr);
		}

	private:
		NodePtr create_node(const ParameterType value)
		{
			NodePtr node = new NodeType;
			node->parent = node->left = node->right = nullptr;
			node->value = value;
			return node;
		}
		void copy(const SearchTree& st)
		{
			__copy(&head, nullptr, st.head);
		}

		//����ֻ�ܲ�ȡ����ķ�ʽ���У�Ҫ����
		//�ڵ��й��������ȹ��츸�ڵ�
		void __copy(BasePtr* dst,BasePtr p, BasePtr src)
		{
			if (src == nullptr)
			{
				*dst = nullptr;
				return;
			}
			*dst = create_node(((NodePtr)src)->value);
			(*dst)->parent = p;
			++size;
			__copy(&((*dst)->left),*dst, src->left);
			__copy(&((*dst)->right),*dst,src->right);
		}

		//�ݻ���ò�ȡ����ķ�ʽ���У�
		//����˼����������Ȼ����
		void _destroy(BasePtr p)
		{
			if (p == nullptr) return;
			_destroy(p->left);
			_destroy(p->right);
			delete (NodePtr)p;
		}

		//ɾ��һ���ڵ������鷳�Ĳ���
		void erase(BasePtr node)
		{
			if (node == nullptr) return;


			//�����ɾ���Ľڵ�ֻ��һ���ӽڵ�
			//��ֱ���ýڵ�ĸ��ڵ��ƹ�����ָ��
			//�����ӽڵ�ͺ��ˣ�����֮���Ը��ӣ�
			//����Ϊ��Ҫ���Ǹ��ڵ��Ƿ�Ϊ�գ��Լ�
			//����ڵ������ʱҪ����parentָ�룬
			//��ά��parentָ������Ϊ��֧�ֵ�����


			//ֻ���ҽڵ�
			if (node->left == nullptr)
			{
				BasePtr p = node;
				node = node->right;
				BasePtr q = parent(p);
				if(node != nullptr) node->parent = q;
				if (p == head) head = node;
				else
				{
					if (q->left == p) q->left = node;
					else q->right = node;
				}
				
				delete NodePtr(p);
			}
			//ֻ���ҽڵ�
			else if (node->right == nullptr)
			{
				BasePtr p = node;
				node = node->left;
				BasePtr q = parent(p);
				if (node != nullptr) node->parent = q;
				if (p == head) head = node;
				else
				{
					if (q->left == p) q->left = node;
					else q->right = node;
				}
				delete NodePtr(p);
			}
			//�������������������û���ӽڵ�����

			//��ɾ���ڵ���������ڵ㣬���ݲ��Ҷ����������ʣ�
			//ʹ�����������е����ֵ�����ɾ���ڵ㣬���������ֵ
			//�ڵ�Ҫôĳ���ڵ�����ӽڵ㣬Ҫô���Ǵ�ɾ���ڵ��
			//���ӽڵ�
			else
			{
				BasePtr p = (node->left)->maximum(); 
				BasePtr q = p->parent;     //��Ϊnode�������ӽڵ㣬����p��parent����Ϊ��

				//�Ѵ�ɾ���ڵ��ֵ�滻Ϊ���������е�
				//���ֵ��ʵ����ֱ�ӽ��ڵ�����滻������
				//�ڽڵ�ֵΪ�ಢӵ����������ʱЧ�ʸ��ߣ�
				//ֻ��ָ�����������һ��
				((NodePtr)node)->value = ((NodePtr)p)->value;

				//���ֵ��ĳ���ڵ�����ӽڵ㣬
				//����Сֵ�ڵ����ӵ��һ��������
				//���������о���һ��ֵ��������
				//���ǵ������ֵ�ڵ��������
				if (q != node)
				{ 
					q->right = p->left; 	
				}
				//��Сֵ�����ӽڵ㣬��ʱ�����������һ��
				//�����������ǵ������ֵ�ڵ��������
				else 
				{ 
					q->left = p->left;
				}
				//����ʱ����parentָ��
				if (p->left != nullptr) p->left->parent = q;
				delete NodePtr(p);
			}
			--size;
		}
		void insert(BasePtr* parent, BasePtr node)
		{
			node->parent = *parent;
			if (*parent == nullptr)
				head = node;
			else if (compare((NodePtr(node))->value, ((NodePtr)(*parent))->value))
				(*parent)->left = node;
			else
				(*parent)->right = node;
			++size;
		}

		void create_head(const ParameterType value)
		{
			head = create_node(value);
			++size;
		}
		BasePtr left(const BasePtr node){ if (node) return node->left; else return nullptr; }
		BasePtr right(const BasePtr node){ if (node) return node->right; else return nullptr; }
		BasePtr parent(const BasePtr node){ if (node) return node->parent; else return nullptr; }
		BasePtr find_first(BasePtr h,const ParameterType value,BasePtr* last_visited_valid_node)
		{
			BasePtr res = nullptr;
			BasePtr p = h;
			*last_visited_valid_node = nullptr;
			while (p)
			{
				*last_visited_valid_node = p;
				if (compare(value, ((NodePtr)p)->value)) p = p->left;
				else if (value == ((NodePtr)p)->value){ res = p; break; }
				else p = p->right;
			}
			return res;
		}
		//�������ظ�����ô���ݲ����㷨���������ظ�ֵ�����嵽��һ��ֵ
		//���������У���δ�ؾ����������ӽڵ㣬���Բ��ҵ�һ���ڵ��
		//��Ҫ�ڸýڵ���������м�������
		BasePtr find_last(BasePtr h,const ParameterType value, BasePtr* last_visited_valid_node)
		{
			BasePtr res = find_first(h,value, last_visited_valid_node);
			if (res != nullptr)
			{
				BasePtr last_visited_valid_node_1 = nullptr;
				BasePtr res_1 = find_first(res->right, value, &last_visited_valid_node_1);
				if (res_1 != nullptr)
				{
					res = res_1;
					*last_visited_valid_node = last_visited_valid_node_1;
				}
			}
			return res;
		}
		//�ҵ�λ��һ���ǲ���ڵ�ĸ��ڵ�
		BasePtr find_position_for_insert(const ParameterType value)
		{
			BasePtr res = nullptr;
			BasePtr p = head;
			while (p)
			{
				res = p;
				if (compare(value, ((NodePtr)p)->value)) p = p->left;
				else p = p->right;
			}
			return res;
		}
		
	private:
		BasePtr head;
		int size;
		Compare compare;
	};
}

#endif