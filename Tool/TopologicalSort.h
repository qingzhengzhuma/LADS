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
		//��ʼ��ÿ���ڵ�������
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
				//�ƽڵ�����Ϊ��ֵ
				--InDgreeCount[i];
			}
		}
		//Ϊ�˱���ÿ��Ѱ�����Ϊ0�Ľڵ㣬����һ��ջ
		//��¼���µ����Ϊ0�Ľڵ㣬�ö��С������ǿ��Ե�
		stack<int> zeroDegreeV;
		for (int i = 0; i < size; ++i)
		{
			if (InDgreeCount[i] == 0) zeroDegreeV.push(i);
		}

		SortedVertices.Clear();
		int UnSortedVerticeCount = Graph.GetVerticeCount();
		//���ջ�գ�˵��û�����Ϊ0�Ľڵ���
		//��ʱҪô���нڵ�������Ҫôͼ���л���
		//�������ز�����
		while (zeroDegreeV.empty() != true)
		{
			int v = zeroDegreeV.top();
			SortedVertices.PushBack(v);
			zeroDegreeV.pop();
			VerticePtr v_ptr = Graph.GetVertice(v);
			//�õ�һ���ڵ�󣬾͵ݼ��Ըö���Ϊ�����յ�
			//�����
			EdgePtr e = v_ptr->adj;
			while (e != nullptr)
			{
				--InDgreeCount[e->dst];
				//���ĳ���ڵ�ݼ�Ϊ0����ô��������һ���ڵ�ĺ�ѡ�ߣ�
				//���õ��������ڵ����һ�εݼ�����ڵ����ȣ���Ϊ�ڵݼ���Ϊ-1��
				//�����ظ������ѡ��ջ��Ҳ����Ӻ�ѡ��ջ��ɾ����������һ���ܾ�λ
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