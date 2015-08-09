#ifndef _TOPOLOGICALSORT_H_
#define _TOPOLOGICALSORT_H_

#include "../include/DirectedWeightGraph.h"
#include "../include/Vector.h"
#include <stack>
using namespace MyDataStructure;
using namespace std;


namespace MyTools
{
	template<typename ValueType, typename WeightType>
	bool TopologicalSort(const DirectedWeightGraph<ValueType, WeightType>& Graph,Vector<int>& SortedVertices)
	{
		typedef typename DirectedWeightGraph<ValueType, WeightType>::VerticePtr VerticePtr;
		typedef typename DirectedWeightGraph<ValueType, WeightType>::EdgePtr EdgePtr;
		int size = Graph.GetVerticeSize();
		if (size <= 0) return false;
		//初始化每个节点的入度数
		Vector<int> InDgreeCount(size);
		for (int i = 0; i < size; ++i)
		{
			VerticePtr v_ptr = Graph.GetVertice(i);
			if (v_ptr != nullptr)
			{
				EdgePtr e = v_ptr->adj;
				while (e != nullptr)
				{
					++InDgreeCount[e->dst];
					e = e->next;
				}
			}
			else
			{
				//哑节点的入度为负值
				--InDgreeCount[i];
			}
		}
		//为了避免每次寻找入度为0的节点，利用一个栈
		//记录最新的入度为0的节点，用队列、链表都是可以的
		stack<int> zeroDegreeV;
		for (int i = 0; i < size; ++i)
		{
			if (InDgreeCount[i] == 0) zeroDegreeV.push(i);
		}

		SortedVertices.Clear();
		int UnSortedVerticeCount = Graph.GetVerticeCount();
		//如果栈空，说明没有入度为0的节点了
		//此时要么所有节点已排序，要么图中有环，
		//不可以拓补排序
		while (zeroDegreeV.empty() != true)
		{
			int v = zeroDegreeV.top();
			SortedVertices.PushBack(v);
			zeroDegreeV.pop();
			VerticePtr v_ptr = Graph.GetVertice(v);
			//得到一个节点后，就递减以该顶点为起点的终点
			//入度数
			EdgePtr e = v_ptr->adj;
			while (e != nullptr)
			{
				--InDgreeCount[e->dst];
				//如果某个节点递减为0，那么它就是下一个节点的候选者，
				//不用担心其他节点会再一次递减这个节点的入度，因为在递减就为-1，
				//不会重复加入候选者栈，也不会从候选者栈中删除，所以它一定能就位
				if (InDgreeCount[e->dst] == 0) zeroDegreeV.push(e->dst);
				e = e->next;
			}
			--UnSortedVerticeCount;
		}
		if (UnSortedVerticeCount != 0)
		{
			SortedVertices.Clear();
			return false;
		}
		return true;
	}
}

#endif