#ifndef _SEARCHTREEITERATORBASE_H_
#define _SEARCHTREEITERATORBASE_H_

namespace MyDataStructure
{
	//查找树迭代器基类
	struct  SearchTreeIteratorBase
	{
		typedef BinaryNodeBase::BasePtr BasePtr;
		BasePtr node;

		//让迭代器移动到下一个节点
		void Increament()
		{
			//如果迭代器指示的节点有右子节点，
			//则以该右子节点为根的树的最小值节
			//点就是下一个迭代器该指示的节点
			if (node->right) node = node->right->minimum();
			else
			{
				//否则，如果当前指示的节点是右子节
				//点，就需要往上搜索第一个不是右子节点
				//的节点，如果当前指示的节点是左子节点，
				//那么父节点就是了。画图根据查找树的性质容易
				//的到算法
				BasePtr p = node->parent;
				//根节点的父节点为nullptr,需要注意
				while (p && p->right == node)
				{
					node = p;
					p = p->parent;
				}
				node = p;
			}
		}

		//让迭代器移动到上一个节点，和Increament
		//算法大同小异，对称地考虑
		void Decreament()
		{
			if (node->left) node = node->left->maximum();
			else
			{
				BasePtr p = node->parent;
				while (p && p->left == node)
				{
					node = p;
					p = p->parent;
				}
				node = p;
			}
		}

		//模拟指针行为，迭代器是一种智能指针
		bool operator ==(const SearchTreeIteratorBase& it)
		{
			return this->node == it.node;
		}

		bool operator != (const SearchTreeIteratorBase& it)
		{
			return this->node != it.node;
		}
	};
}

#endif