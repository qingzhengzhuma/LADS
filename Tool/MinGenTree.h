#ifndef _MINGENTREE_H_
#define _MINGENTREE_H_

#include "../include/DirectedWeightGraph.h"
#include "../include/Vector.h"
#include "../include/UnionFindSet.h"
#include "../include/Heap.h"
using namespace MyDataStructure;

namespace MyTools
{
	template <typename ValueType,typename WeightType>
	class MinGenTree
	{
	public:
		typedef typename DirectedWeightGraph<ValueType, WeightType> GraphType;
		typedef typename GraphType::VerticePtr VerticePtr;
		typedef typename GraphType::EdgePtr EdgePtr;
	public:
		Vector<EdgePtr> Kruscal(const GraphType &Graph)
		{
			int size = Graph.GetVerticeSize();
			//算法的核心是，每一步选择一条具有最小
			//权值并且加入最小生成树后不会产生回路
			//的边，可以利用一个最小堆动态排序边
			Heap<EdgePtr, less> minHeap;
			for (int i = 0; i < size; ++i)
			{
				VerticePtr v = Graph.GetVertice(i);
				if (v != nullptr)
				{
					EdgePtr e = v->adj;
					while (e != nullptr)
					{
						minHeap.Insert(e);
						e = e->next;
					}
				}
			}
			//利用并查集判断边一条候选边加入后
			//是否会产生回路
			UnionFindSet ufs(size);
			Vector<EdgePtr> minTree;
			int VerticeCount = Graph.GetVerticeCount();
			while (minHeap.Size() != 0 && minTree.Size() < VerticeCount)
			{
				EdgePtr e;
				if (minHeap.GetTop(e))
				{
					minHeap.RemoveTop();
					//如果当前最小一条边的两个顶点不同时在最小生成树
					//集合或剩余的图里，那么这条边就可以加入最小生成树，
					//就不会产生回路
					if (ufs.Find(e->src) != ufs.Find(e->dst))
					{
						minTree.PushBack(e);
						ufs.Union(e->src, e->dst);
					}
				}
			}
			//如果最小生成树的边的数目不是顶点数减一，那这棵树就不是一棵最小生成树
			if (minTree.Size() < VerticeCount - 1) return Vector<EdgePtr>();
			else return minTree;
		}
		Vector<EdgePtr> Prim(const GraphType Graph)
		{
			int size = Graph.GetVerticeSize();
			//算法的核心是每次从跨越最小生成树集合与
			//剩余图的集合的边中选择具有最小权值的一条边
			//加入生成树，所以可以利用最小堆动态排序跨越
			//两个集合的边
			Heap<EdgePtr, less> minHeap;

			Vector<EdgePtr> minTreeEdge;
			//只有一条边的一个顶点在生成树中，而另一个顶点
			//不在，才有可能被选择
			Vector<bool> IsInMST(size);
			for (int i = 0; i < size; ++i)
			{
				IsInMST[i] = false;
			}
			//选择一个顶点开始
			Vector<int> minTreeVertice;
			for (int i = 0; i < size; ++i)
			{
				if (Graph.GetVertice(i) != nullptr)
				{
					minTreeVertice.PushBack(i);
					IsInMST[i] = true;
					break;
				}
			}
			int VerticeCount = Graph.GetVerticeCount();
			do
			{
				int mst_v = minTreeVertice.Size();
				EdgePtr e = Graph.GetVertice(minTreeVertice[mst_v - 1])->adj;
				//找到新加入的顶点带来的跨越两个集合的边，加入最小堆，作为候选点
				while (e != nullptr)
				{
					if (IsInMST[e->dst] == false) minHeap.Insert(e);
					e = e->next;
				}
				EdgePtr top = nullptr;
				//由于加入了一个新的节点，所以以前的一些候选边由于两个
				//顶点都在最小生成树集合里而不能再被选择，但它们又可能
				//处于最小堆的顶端，把这种边移除
				while (minHeap.GetTop(top) == true && IsInMST[top->dst] == true)
				{
					minHeap.RemoveTop();
					top = nullptr;
				}
				//除非堆中还有可用的边，否则就退出循环了
				if (top != nullptr)
				{
					if (IsInMST[top->dst] = true)
					{
						minHeap.RemoveTop();
						minTreeVertice.PushBack(top->dst);
						minTreeEdge.PushBack(top);
						IsInMST[top->dst] = true;
					}
				}
				else
				{
					break;
				}
			} while (minTreeVertice.Size() < VerticeCount);
			//如果最小生成树的边的数目不是顶点数减一，那这棵树就不是一棵最小生成树
			if (minTreeEdge.Size() < VerticeCount - 1) return Vector<EdgePtr>();
			else return minTreeEdge;
		}
	private:
		struct less
		{
			bool operator ()(const EdgePtr op1, const EdgePtr op2)
			{
				return op1->weight < op2->weight;
			}
		};
	};
}

#endif