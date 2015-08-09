#ifndef _HOFFMAN_H_
#define _HOFFMAN_H_

#include "../include/Vector.h"
#include "../include/Heap.h"
#include "../Utilites/type_traits.h"
#include "../include/Functor.h"

namespace MyDataStructure
{
	template<typename WeightType>
	struct HoffmanNode
	{
		int index;
		WeightType weight;
		HoffmanNode* left;
		HoffmanNode* right;
	};

	//针对HoffmanNode指针特化一个大于比较仿函数，构造
	//最小堆的的时候需要，最小堆中的元素是HoffmanNode
	//型指针
	template<typename WeightType>
	struct less<HoffmanNode<WeightType>*>
	{
		bool operator ()(HoffmanNode<WeightType>* op1, HoffmanNode<WeightType>* op2)
		{
			return op1->weight < op2->weight;
		}
	};
	template <typename ValueType, typename WeightType>
	class HoffmanTree
	{	
	public:
		typedef typename ParameterTrait<WeightType>::ParameterType WeightParameterType;
		typedef typename HoffmanNode< WeightType>* NodePtr;
		typedef typename HoffmanNode< WeightType> NodeType;
		typedef typename HoffmanTree<ValueType, WeightType> self;
	public:
		HoffmanTree(ValueType values[],WeightType weights[],int count);
		HoffmanTree(const HoffmanTree& rhs);
		self& operator = (const HoffmanTree& rhs);
		~HoffmanTree();
		void Clear();
		NodePtr GetHead(){ return head; }
	private:
		NodePtr create_node(int index, WeightParameterType weight);
		NodePtr copy_node(const NodePtr node);
		NodePtr merge_node(NodePtr left, NodePtr right);
		void copy(const HoffmanTree& rhs);
		void __copy_tree(NodePtr* dst_node,NodePtr start_node);
		void __clear_tree(NodePtr start_node);
		void create_tree(ValueType values[], WeightType weights[], int count);
		void clear();
	private:
		NodePtr head;
		Vector<ValueType> values;
		Vector<WeightType> weights;
	};

	template<typename ValueType, typename WeightType>
	HoffmanTree<ValueType, WeightType>::HoffmanTree(ValueType values[], WeightType weights[], int count)
	{
		create_tree( values,weights, count);
	}

	template<typename ValueType, typename WeightType>
	HoffmanTree<ValueType, WeightType>::HoffmanTree(const HoffmanTree& rhs)
	{
		clear();
		copy(rhs);
	}

	template<typename ValueType, typename WeightType>
	typename HoffmanTree<ValueType, WeightType>& HoffmanTree<ValueType, WeightType>
		::operator =(const HoffmanTree& rhs)
	{
		clear();
		copy(rhs);
		return *this;
	}

	template<typename ValueType, typename WeightType>
	HoffmanTree<ValueType, WeightType>::~HoffmanTree()
	{
		clear();
	}

	template<typename ValueType, typename WeightType>
	void HoffmanTree<ValueType, WeightType>::Clear()
	{
		clear();
	}

	template<typename ValueType, typename WeightType>
	typename HoffmanTree<ValueType, WeightType>::NodePtr
		HoffmanTree<ValueType, WeightType>
		::create_node(int index, WeightParameterType weight)
	{
		NodeType* node = new NodeType;
		node->left = node->right = nullptr;
		node->index = index;
		node->weight = weight;
		return node;
	}

	template<typename ValueType, typename WeightType>
	typename HoffmanTree<ValueType, WeightType>::NodePtr
		HoffmanTree<ValueType, WeightType>
		::copy_node(const NodePtr node)
	{
		return create_node(node->index, node->weight);
	}

	template<typename ValueType, typename WeightType>
	typename HoffmanTree<ValueType, WeightType>::NodePtr
		HoffmanTree<ValueType, WeightType>
		::merge_node(NodePtr left, NodePtr right)
	{
		NodeType* node = new NodeType;
		node->left = left;
		node->right = right;
		node->weight = left->weight + right->weight;
		//用index = -1表示这是一个内部节点
		node->index = -1;
		return node;
	}

	template<typename ValueType, typename WeightType>
	void HoffmanTree<ValueType, WeightType>
		::copy(const HoffmanTree& rhs)
	{
		values = rhs.values;
		weights = rhs.weights;
		__copy_tree(&head, rhs.head);
	}

	template<typename ValueType, typename WeightType>
	void HoffmanTree<ValueType, WeightType>
		::__copy_tree(NodePtr* dst_node, NodePtr start_node)
	{
		if (start_node == nullptr) *dst_node = nullptr;
		else
		{
			NodeType* node = copy_node(start_node);
			*dst_node = node;
			__copy_tree(&((*dst_node)->left), start_node->left);
			__copy_tree(&((*dst_node)->right), start_node->right);
		}
	}

	template<typename ValueType, typename WeightType>
	void HoffmanTree<ValueType, WeightType>::clear()
	{
		__clear_tree(head);
		values.Clear();
	}

	template<typename ValueType, typename WeightType>
	void HoffmanTree<ValueType, WeightType>
		::__clear_tree(NodePtr start_node)
	{
		if (start_node == nullptr) return;
		else
		{
			if (start_node->left != nullptr) __clear_tree(start_node->left);
			if (start_node->right != nullptr) __clear_tree(start_node->right);
			delete start_node;
			start_node = nullptr;
		}
	}

	template<typename ValueType, typename WeightType>
	void HoffmanTree<ValueType, WeightType>
		::create_tree(ValueType values[], WeightType weights[], int count)
	{
		Heap<NodePtr, less<NodePtr>> minHeap;
		for (int i = 0; i < count; ++i) 
		{
			NodeType* node = create_node(i, weights[i]);
			this->values.PushBack(values[i]);
			this->weights.PushBack(weights[i]);
			minHeap.Insert(node);
		}
		while (minHeap.Size() > 1)
		{
			NodePtr node1,node2;
			minHeap.GetTop(node1);
			minHeap.RemoveTop();
			minHeap.GetTop(node2);
			minHeap.RemoveTop();
			NodePtr new_node = merge_node(node1, node2);
			minHeap.Insert(new_node);
		}
		minHeap.GetTop(head);
	}
}

#endif