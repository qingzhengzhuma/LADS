#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include "BinaryNodeBase.h"
#include "SearchTreeIteratorBase.h"
#include "../Utilites/type_traits.h"
#include "Functor.h"

namespace MyDataStructure
{
	template <typename ValueType>
	struct AVLTreeNode : public BinaryNodeBase
	{
		typedef BinaryNodeBase* LinkType;
		ValueType value;
		int balance_factor;
	};

	template <typename Value,typename Ref,typename Ptr>
	struct AVLTreeIterator : public SearchTreeIteratorBase
	{
		typedef Value ValueType;
		typedef Ref reference;
		typedef Ptr pointer;
		typedef AVLTreeIterator<ValueType, ValueType&, ValueType*> iterator;
		typedef AVLTreeIterator<ValueType, const ValueType&, ValueType*> const_iterator;
		typedef AVLTreeIterator<ValueType, ValueType&,ValueType*> self;
		typedef BinaryNodeBase* BasePtr;
		typedef AVLTreeNode<ValueType>* NodePtr;

		AVLTreeIterator(){ node = nullptr; }
		AVLTreeIterator(BasePtr node) { this->node = node; }
		AVLTreeIterator(const iterator& rhs){ this->node = rhs.node; }
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
	class AVLTree
	{
	public:
		typedef typename ParameterTrait<T>::ParameterType ParameterType;
		typedef typename AVLTreeNode<T> NodeType;
		typedef typename AVLTreeNode<T>* NodePtr;
		typedef typename AVLTreeNode<T>::BasePtr BasePtr;
		typedef typename AVLTreeIterator<T, T&, T*>::iterator iterator;
	public:

		//�����ַ�ʽ����һ�ò�������
		//  1������һ�ſ�����
		//  2������һ���Ѿ����ڵ���
		AVLTree() : size(0), head(nullptr){}
		AVLTree(const AVLTree& avlt)
		{
			copy(avlt);
		}
		AVLTree& operator = (const AVLTree& avlt)
		{
			if (&avlt != this)
			{
				Clear();
				copy(avlt);
			}
			return *this;
		}
		~AVLTree(){ Clear(); }
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
			BasePtr p = find_first(head, value, &q);
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
		NodePtr create_node(const ParameterType value)
		{
			NodePtr node = new NodeType;
			node->parent = node->left = node->right = nullptr;
			node->value = value;
			node->balance_factor = 0;
			return node;
		}
		void create_head(const ParameterType value)
		{
			head = create_node(value);
			++size;
		}
		void copy(const AVLTree& st)
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
			*dst = create_node(((NodePtr)src)->value);
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

		//ɾ��һ���ڵ�
		void erase(BasePtr node)
		{
			if (node == nullptr) return;
			BasePtr q = nullptr;
			if (node->left != nullptr && node->right != nullptr)
			{
				q = node->left->maximum();
				NodePtr(node)->value = NodePtr(q)->value;
				node = q;
			}

			if (node->left != nullptr) q = node->left;
			else q = node->right;
			BasePtr pr = node->parent;
			if (pr == nullptr) head = q;
			else
			{
				if (pr->left == node) pr->left = q;
				else pr->right = q;
				if (q != nullptr) q->parent = pr;
				while (pr != nullptr)
				{
					if (pr->right == q) --NodePtr(pr)->balance_factor;
					else ++NodePtr(pr)->balance_factor;
					BasePtr s = pr->parent;
					int dd = 0;
					if (s != nullptr)
					{
						dd = s->left == pr ? -1 : 1;
					}
					if (NodePtr(pr)->balance_factor == 1 || NodePtr(pr)->balance_factor == -1) break;
					if (NodePtr(pr)->balance_factor != 0)
					{
						int d = 1;
						if (NodePtr(pr)->balance_factor < 0)
						{
							d = -1;
							q = pr->left;
						}
						else q = pr->right;
						if (NodePtr(q)->balance_factor == 0)
						{
							if (d == -1)
							{
								RRotate(&pr);
								NodePtr(pr)->balance_factor = 1;
								NodePtr(pr->left)->balance_factor = -1;
							}
							else
							{
								LRotate(&pr);
								NodePtr(pr)->balance_factor = -1;
								NodePtr(pr->right)->balance_factor = 1;
							}
							break;
						}
						if (NodePtr(q)->balance_factor == d)
						{
							if (d == -1) RRotate(&pr);
							else LRotate(&pr);
						}
						else
						{
							if (d == -1) LRRotate(&pr);
							else RLRotate(&pr);
						}
						if (dd == -1) s->left = pr;
						else if (dd == 1) s->right = pr;
						pr->parent = s;
					}
					q = pr;
					pr = NodePtr(pr->parent);
				}
				if (pr == nullptr) head = q;
			}
			delete node;
		}
		void insert(BasePtr* parent, BasePtr node)
		{
			if (node == nullptr) return;
			BasePtr q = *parent;
			node->parent = q;
			if (q == nullptr)
				head = node;
			else if (compare((NodePtr(node))->value, (NodePtr(q)->value)))
			{
				q->left = node;
				--NodePtr(q)->balance_factor;
			}
				
			else
			{
				q->right = node;
				++NodePtr(q)->balance_factor;
			}
			++size;
			if (NodePtr(q)->balance_factor == 0) return;

			BasePtr s = q->parent;
			while (s)
			{
				if (s->left == q) --NodePtr(s)->balance_factor;
				else ++NodePtr(s)->balance_factor;
				if (NodePtr(s)->balance_factor == 0) return;
				else if (NodePtr(s)->balance_factor == -1 || NodePtr(s)->balance_factor == 1)
				{
					q = s;
					s = s->parent;
				}
				else
				{
					int d = NodePtr(s)->balance_factor < 0 ? -1 : 1;
					if (d == NodePtr(q)->balance_factor)
					{
						if (d < 0) RRotate(&s);
						else LRotate(&s);
					}
					else
					{
						if (d < 0) LRRotate(&s);
						else RLRotate(&s);
					}
					break;
				}
			}
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

		void LRotate(BasePtr* p)
		{
			BasePtr ptr = *p;
			BasePtr subL = ptr;
			BasePtr q = parent(ptr);
			ptr = ptr->right;
			ptr->parent = q;
			BasePtr Rofsubl = ptr->left;
			subL->right = Rofsubl;
			if (Rofsubl != nullptr) Rofsubl->parent = subL;
			ptr->left = subL;
			subL->parent = ptr;
			if (q != nullptr)
			{
				if (q->left == subL) q->left = ptr;
				else q->right = ptr;
			}
			else
			{
				head = ptr;
				head->parent = nullptr;
			}

			NodePtr(ptr)->balance_factor = 0;
			NodePtr(subL)->balance_factor = 0;
		}

		void RRotate(BasePtr* p)
		{
			BasePtr ptr = *p;
			BasePtr subR = ptr;
			BasePtr q = ptr->parent;
			ptr = ptr->left;
			ptr->parent = q;
			BasePtr LofSubR = ptr->right;
			subR->left = LofSubR;
			if (LofSubR != nullptr) LofSubR->parent = subR;
			ptr->right = subR;
			subR->parent = ptr;
			if (q != nullptr)
			{
				if (q->left == subR) q->left = ptr;
				else q->right = ptr;
			}
			else
			{
				head = ptr;
				head->parent = nullptr;
			}
			NodePtr(ptr)->balance_factor = 0;
			NodePtr(subR)->balance_factor = 0;
		}

		void LRRotate(BasePtr* p)
		{
			BasePtr ptr = *p;
			BasePtr subR = ptr;
			BasePtr subL = subR->left;
			ptr = subL->right;

			subL->right = ptr->left;
			ptr->left->parent = subL;
			ptr->left = subL;
			subL->parent = ptr;

			if (NodePtr(ptr)->balance_factor <= 0) NodePtr(subL)->balance_factor = 0;
			else NodePtr(subL)->balance_factor = -1;

			subR->left = ptr->right;
			ptr->right->parent = subR;
			BasePtr q = subR->parent;
			if (q != nullptr)
			{
				if (q->left == subR) q->left = ptr;
				else q->right = ptr;
			}
			else head = ptr;
			ptr->right = subR;
			subR->parent = ptr;
			ptr->parent = q;

			if (NodePtr(ptr)->balance_factor == -1) NodePtr(subR)->balance_factor = 1;
			else NodePtr(subR)->balance_factor = 0;

			NodePtr(ptr)->balance_factor = 0;
		}

		void RLRotate(BasePtr* p)
		{
			BasePtr ptr = *p;
			BasePtr subL = ptr;
			BasePtr subR = subL->right;
			ptr = subR->left;

			subR->left = ptr->right;
			ptr->right->parent = subR;
			ptr->right = subR;
			subR->parent = ptr;

			if (NodePtr(ptr)->balance_factor >= 0) NodePtr(subR)->balance_factor = 0;
			else NodePtr(subR)->balance_factor = 1;

			
			subL->right = ptr->left;
			if (ptr->left != nullptr) ptr->left->parent = subL;
			BasePtr q = subL->parent;
			if (q != nullptr)
			{
				if (q->left == subL) q->left = ptr;
				else q->right = ptr;
			}
			else head = ptr;
			ptr->left = subL;
			subL->parent = ptr;
			ptr->parent = q;

			if (NodePtr(ptr)->balance_factor == 1) NodePtr(subL)->balance_factor = -1;
			else NodePtr(subL)->balance_factor = 0;
			NodePtr(ptr)->balance_factor = 0;
		}

	private:
		BasePtr head;
		int size;
		Compare compare;
	};
}

#endif