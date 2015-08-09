#ifndef _RBTREE_H_
#define _RBTREE_H_
#include "../Utilites/type_traits.h"
#include "Functor.h"
#include "BinaryNodeBase.h"
#include "SearchTreeIteratorBase.h"

namespace MyDataStructure
{
#define  red true
#define  black false
	typedef bool Color;

	template <typename Value>
	struct rb_node : public BinaryNodeBase
	{
		Color color;
		Value value;
	};

	template <typename Value, typename Ref, typename Ptr>
	struct RBTreeIterator : public SearchTreeIteratorBase
	{
		typedef Value ValueType;
		typedef Ref reference;
		typedef Ptr pointer;
		typedef RBTreeIterator<ValueType, ValueType&, ValueType*> iterator;
		typedef RBTreeIterator<ValueType, const ValueType&, ValueType*> const_iterator;
		typedef RBTreeIterator<ValueType, ValueType&, ValueType*> self;
		typedef BinaryNodeBase* BasePtr;
		typedef rb_node<ValueType>* NodePtr;

		RBTreeIterator(){ node = nullptr; }
		RBTreeIterator(BasePtr node) { this->node = node; }
		RBTreeIterator(const iterator& rhs){ this->node = rhs.node; }
		self& operator =(const iterator& rhs){ this->node = rhs.node; return *this; }

		reference operator *(){ return NodePtr(node)->value; }
		pointer operator ->(){ return &(operator*()); }

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
	class RBTree
	{
	public:
		typedef typename ParameterTrait<T>::ParameterType ParameterType;
		typedef typename rb_node<T> NodeType;
		typedef typename rb_node<T>* NodePtr;
		typedef typename rb_node<T>::BasePtr BasePtr;
		typedef typename RBTreeIterator<T, T&, T*>::iterator iterator;
	public:

		//�����ַ�ʽ����һ�ò�������
		//  1������һ�ſ�����
		//  2������һ���Ѿ����ڵ���
		RBTree() : size(0), head(nullptr){}
		RBTree(const RBTree& rbt)
		{
			copy(rbt);
		}
		RBTree& operator = (const RBTree& rbt)
		{
			if (&rbt != this)
			{
				Clear();
				copy(rbt);
			}
			return *this;
		}
		~RBTree(){ Clear(); }
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
			NodePtr node = create_red_node(value);
			insert(q, node);
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
			BasePtr p = find_first(head, value, &q);
			if (q == nullptr)
			{
				create_head(value);
			}
			else
			{
				//p��Ϊ�գ���������ظ�ֵ������ʲôҲ������
				if (p != nullptr) return;
				NodePtr node = create_red_node(value);
				insert(&q, node);
			}
		}

		iterator FindFirst(const ParameterType value)
		{
			BasePtr temp = nullptr;
			return iterator(find_first(head, value, &temp));
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
		NodePtr create_red_node(const ParameterType value)
		{
			NodePtr node = new NodeType;
			node->parent = node->left = node->right = nullptr;
			node->value = value;
			node->color = red;
			return node;
		}

		void copy(const RBTree& st)
		{
			__copy(&head, nullptr, st.head);
		}

		//����ֻ�ܲ�ȡ����ķ�ʽ���У�Ҫ����
		//�ڵ��й��������ȹ��츸�ڵ�
		void __copy(BasePtr* dst, BasePtr p, BasePtr src)
		{
			if (src == nullptr)
			{
				*dst = nullptr;
				return;
			}
			*dst = create_red_node(((NodePtr)src)->value);
			(*dst)->parent = p;
			++size;
			__copy(&((*dst)->left), *dst, src->left);
			__copy(&((*dst)->right), *dst, src->right);
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

		void transplant(BasePtr y, BasePtr x)
		{
			BasePtr q = y->parent;
			if (q == nullptr)
			{
				x->parent = nullptr;
				head = x;
			}
			else
			{
				if (q->left == y) q->left = x;
				else q->right = x;
				if(x != nullptr) x->parent = q;
			}
		}

		//ɾ��һ���ڵ�
		void erase(BasePtr node)
		{
			if (node == nullptr) return;
			BasePtr y = node;
			Color old_color = NodePtr(y)->color;
			BasePtr x = nullptr;
			if (y->left == nullptr)
			{
				x = y->right;
				transplant(y, x);
			}
			else if (y->right == nullptr)
			{
				x = y->left;
				transplant(y, x);
			}
			else
			{
				y = y->right->minimum();
				old_color = NodePtr(y)->color;
				x = y->right;
				if (y->parent != node)
				{
					transplant(y, x);
					y->right = node->right;
					node->right->parent = y;
				}
				transplant(node, y);
				y->left = node->left;
				node->left->parent = y;
				NodePtr(y)->color = NodePtr(node)->color;
			}
			delete NodePtr(node);
			--size;
			if (old_color == black)
				erase_fixup(x);
		}
		void insert(BasePtr parent, BasePtr node)
		{
			if (node == nullptr) return;
			BasePtr q = parent;
			node->parent = q;
			if (q == nullptr)
				head = node;
			else if (compare((NodePtr(node))->value, (NodePtr(q)->value)))
			{
				q->left = node;
			}
			else
			{
				q->right = node;
			}
			++size;
			insert_fixup(node);
		}


		BasePtr left(const BasePtr node){ if (node) return node->left; else return nullptr; }
		BasePtr right(const BasePtr node){ if (node) return node->right; else return nullptr; }
		BasePtr parent(const BasePtr node){ if (node) return node->parent; else return nullptr; }
		BasePtr find_first(BasePtr h, const ParameterType value, BasePtr* last_visited_valid_node)
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
		BasePtr find_last(BasePtr h, const ParameterType value, BasePtr* last_visited_valid_node)
		{
			BasePtr res = find_first(h, value, last_visited_valid_node);
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

		void LRotate(BasePtr ptr)
		{
			if (ptr == nullptr) return;
			BasePtr subR = ptr->right;
			if (subR == nullptr) return;
			BasePtr q = ptr->parent;
			ptr->right = subR->left;
			if (subR->left != nullptr) subR->left->parent = ptr;
			subR->left = ptr;
			ptr->parent = subR;
			subR->parent = q;
			if (q != nullptr)
			{
				if (q->left == ptr) q->left = subR;
				else q->right = subR;
			}
			else head = subR;
		}

		void RRotate(BasePtr ptr)
		{
			if (ptr == nullptr) return;
			BasePtr subL = ptr->left;
			if (subL == nullptr) return;
			BasePtr q = ptr->parent;
			ptr->left = subL->right;
			if (subL->right != nullptr) subL->right->parent = ptr;
			subL->right = ptr;
			ptr->parent = subL;
			subL->parent = q;
			if (q != nullptr)
			{
				if (q->left == ptr) q->left = subL;
				else q->right = subL;
			}
			else head = subL;
		}

		void insert_fixup(BasePtr ptr)
		{
			if (ptr == nullptr) return;
			BasePtr q = ptr->parent;
			while (q != nullptr && NodePtr(q)->color == red)
			{
				BasePtr g = q->parent;
				if (g != nullptr)
				{
					if (g->left == q)
					{
						BasePtr y = g->right;
						if (y != nullptr && NodePtr(y)->color == red)
						{
							NodePtr(q)->color = black;
							NodePtr(y)->color = black;
							NodePtr(g)->color = red;
							ptr = g;
						}
						else 
						{
							if (ptr == q->right)
							{
								ptr = q;
								LRotate(ptr);
							}
							NodePtr(ptr->parent)->color = black;
							NodePtr(g)->color = red;
							RRotate(g);	
						}
						q = ptr->parent;
					}
					else
					{
						BasePtr y = g->left;
						if (y != nullptr && NodePtr(y)->color == red)
						{
							NodePtr(q)->color = black;
							NodePtr(y)->color = black;
							NodePtr(g)->color = red;
							ptr = g;
						}
						else 
						{
							if (ptr == q->left)
							{
								ptr = q;
								RRotate(ptr);
							}
							NodePtr(ptr->parent)->color = black;
						    NodePtr(g)->color = red;
						    LRotate(g);
						}
						q = ptr->parent;
					}
				}
				else break;
			}
			NodePtr(head)->color = black;
		}

		void erase_fixup(BasePtr ptr)
		{
			if (ptr == nullptr) return;
			while (ptr != head && NodePtr(ptr)->color == black)
			{
				BasePtr q = ptr->parent;
				if (ptr == q->left)
				{
					BasePtr w = q->right;
					if (w == nullptr) ptr = head;
					else
					{
						if (NodePtr(w)->color == red)
						{
							NodePtr(w)->color = black;
							NodePtr(q)->color = red;
							LRotate(q);
							w = q->right;
						}
						if ((w->left == nullptr || NodePtr(w->left)->color == black) &&
							(w->right == nullptr || NodePtr(w->right)->color == black))
						{
							NodePtr(w)->color = red;
							ptr = q;
						}
						else if ((w->right == nullptr || NodePtr(w->right)->color == black))
						{
							NodePtr(w->left)->color = black;
							NodePtr(w)->color = red;
							RRotate(w);
							w = q->right;
						}
						if (NodePtr(w)->color == black && w->right != nullptr && NodePtr(w->right)->color == red)
						{
							NodePtr(w)->color = NodePtr(q)->color;
							NodePtr(w->right)->color = black;
							NodePtr(q)->color = black;
							LRotate(q);
							ptr = head;
						}
					}
				}
				else
				{
					BasePtr w = q->left;
					if (w == nullptr) ptr = head;
					else
					{
						if (NodePtr(w)->color == red)
						{
							NodePtr(w)->color = black;
							NodePtr(q)->color = red;
							RRotate(q);
							w = q->left;
						}
						if ((w->right == nullptr || NodePtr(w->right)->color == black) &&
							(w->left == nullptr || NodePtr(w->left)->color == black))
						{
							NodePtr(w)->color = red;
							ptr = q;
						}
						else if ((w->left == nullptr || NodePtr(w->left)->color == black))
						{
							NodePtr(w->right)->color = black;
							NodePtr(w)->color = red;
							LRotate(w);
							w = q->left;
						}
						if (NodePtr(w)->color == black && w->left != nullptr && NodePtr(w->left)->color == red)
						{
							NodePtr(w)->color = NodePtr(q)->color;
							NodePtr(w->left)->color = black;
							NodePtr(q)->color = black;
							RRotate(q);
							ptr = head;
						}
					}
				}
			}
			NodePtr(ptr)->color = black;
		}

	private:
		BasePtr head;
		int size;
		Compare compare;
	};
}

#endif