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
			//�㷨�ĺ����ǣ�ÿһ��ѡ��һ��������С
			//Ȩֵ���Ҽ�����С�������󲻻������·
			//�ıߣ���������һ����С�Ѷ�̬�����
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
			//���ò��鼯�жϱ�һ����ѡ�߼����
			//�Ƿ�������·
			UnionFindSet ufs(size);
			Vector<EdgePtr> minTree;
			int VerticeCount = Graph.GetVerticeCount();
			while (minHeap.Size() != 0 && minTree.Size() < VerticeCount)
			{
				EdgePtr e;
				if (minHeap.GetTop(e))
				{
					minHeap.RemoveTop();
					//�����ǰ��Сһ���ߵ��������㲻ͬʱ����С������
					//���ϻ�ʣ���ͼ���ô�����߾Ϳ��Լ�����С��������
					//�Ͳ��������·
					if (ufs.Find(e->src) != ufs.Find(e->dst))
					{
						minTree.PushBack(e);
						ufs.Union(e->src, e->dst);
					}
				}
			}
			//�����С�������ıߵ���Ŀ���Ƕ�������һ����������Ͳ���һ����С������
			if (minTree.Size() < VerticeCount - 1) return Vector<EdgePtr>();
			else return minTree;
		}
		Vector<EdgePtr> Prim(const GraphType Graph)
		{
			int size = Graph.GetVerticeSize();
			//�㷨�ĺ�����ÿ�δӿ�Խ��С������������
			//ʣ��ͼ�ļ��ϵı���ѡ�������СȨֵ��һ����
			//���������������Կ���������С�Ѷ�̬�����Խ
			//�������ϵı�
			Heap<EdgePtr, less> minHeap;

			Vector<EdgePtr> minTreeEdge;
			//ֻ��һ���ߵ�һ���������������У�����һ������
			//���ڣ����п��ܱ�ѡ��
			Vector<bool> IsInMST(size);
			for (int i = 0; i < size; ++i)
			{
				IsInMST[i] = false;
			}
			//ѡ��һ�����㿪ʼ
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
				//�ҵ��¼���Ķ�������Ŀ�Խ�������ϵıߣ�������С�ѣ���Ϊ��ѡ��
				while (e != nullptr)
				{
					if (IsInMST[e->dst] == false) minHeap.Insert(e);
					e = e->next;
				}
				EdgePtr top = nullptr;
				//���ڼ�����һ���µĽڵ㣬������ǰ��һЩ��ѡ����������
				//���㶼����С������������������ٱ�ѡ�񣬵������ֿ���
				//������С�ѵĶ��ˣ������ֱ��Ƴ�
				while (minHeap.GetTop(top) == true && IsInMST[top->dst] == true)
				{
					minHeap.RemoveTop();
					top = nullptr;
				}
				//���Ƕ��л��п��õıߣ�������˳�ѭ����
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
			//�����С�������ıߵ���Ŀ���Ƕ�������һ����������Ͳ���һ����С������
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