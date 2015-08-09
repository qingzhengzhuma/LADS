#ifndef _NOWEIGHTGRAPH_H_
#define _NOWEIGHTGRAPH_H_
#include "../include/Vector.h"

using namespace std;

namespace MyDataStructure
{
	template<typename Value, typename Edge>
	struct Vertice
	{
		typedef Value ValueType;
		typedef Edge* EdgePtr;
		typedef Edge EdgeType;
		ValueType value;
		EdgeType* adj;
	};

	template<typename Weight>
	struct Edge
	{
		typedef Weight WeightType;
		typedef typename Edge<WeightType> EdgeType;
		typedef EdgeType* EdgePtr;
		int src;
		int dst;
		WeightType weight;
		EdgeType* next;
	};


	template<typename Value, typename Weight>
	class DirectedWeightGraph
	{
	public:
		typedef Value ValueType;
		typedef Weight WeightType;
		typedef typename Vertice<ValueType, Edge<WeightType>> VerticeType;
		typedef typename Edge<WeightType> EdgeType;
		typedef VerticeType* VerticePtr;
		typedef EdgeType* EdgePtr;
		typedef DirectedWeightGraph<ValueType, WeightType> self;
		
	public:
		DirectedWeightGraph(){}
		DirectedWeightGraph(ValueType values[], int vertice_count,
			int src[], int dst[], WeightType weight[], int edge_count)
		{
			for (int i = 0; i < vertice_count; ++i)
			{
				AddVertice(values[i]);
			}
			for (int i = 0; i < edge_count; ++i)
			{
				AddEdge(src[i], dst[i], weight[i]);
			}
		}
		DirectedWeightGraph(const Vector<ValueType>& values,
			const Vector<int>& src,const Vector<int>& dst,
			const Vector<WeightType>& weight)
		{
			int vertice_count = values.Size();
			for (int i = 0; i < vertice_count; ++i)
			{
				AddVertice(values[i]);
			}
			int edge_count = weight.Size();
			for (int i = 0; i < edge_count; ++i)
			{
				AddEdge(src[i], dst[i], weight[i]);
			}
		}
		~DirectedWeightGraph(){}
		VerticePtr CreateVertice(ValueType value)
		{
			VerticeType* vertice = new VerticeType;
			vertice->value = value;
			vertice->adj = nullptr;
			return vertice;
		}
		EdgePtr CreateEdge(int src, int dst, WeightType weight)
		{
			EdgeType* edge = new EdgeType;
			edge->src = src;
			edge->dst = dst;
			edge->next = nullptr;
			edge->weight = weight;
			return edge;
		}
		int AddVertice(ValueType value)
		{
			VerticePtr v = CreateVertice(value);
			return AddVertice(v);
		}
		int AddVertice(VerticePtr vertice)
		{
			int size = Vertices.Size();
			int i = 0;
			while (i < size)
			{
				if (Vertices[i] == nullptr)
				{
					Vertices[i] = vertice;
					break;
				}
				++i;
			}
			if (i >= size)
			{
				Vertices.PushBack(vertice);
			}
			++VerticeCount;
			return i;
		}
		bool IsVerticeContianed(int v) const
		{
			if (v < 0 || v >= Vertices.Size()) return false;
			//��Щ�ڵ����Ƶģ������Ľڵ�ռ�ÿռ䣬��ʵ�����ǲ����ڵ�
			return Vertices[v] != nullptr;
		}

		bool IsVerticeContianed(VerticePtr v) const
		{
			if (v == nullptr) return false;
			int size = Vertices.Size();
			for (int i = 0; i < size; ++i)
			{
				if (Vertices[i] == v) return true;
			}
			return false;
		}

		//��������������ж���·������Щ��ͬ·��Ҳ���Ծ���ͬ����Ȩֵ
		bool AddEdge(int src, int dst, WeightType weight)
		{
			if (IsVerticeContianed(src) && IsVerticeContianed(dst) && src != dst)
			{
				EdgeType* e = Vertices[src]->adj;
				Vertices[src]->adj = CreateEdge(src, dst, weight);
				Vertices[src]->adj->next = e;
				++EdgeCount;
				return true;
			}
			return false;
		}
		bool IsConnected(int src, int dst) const 
		{
			if (src == dst) return true;
			if (IsVerticeContianed(src) && IsVerticeContianed(dst))
			{
				EdgePtr e = Vertices[src].adj;
				while (e != nullptr)
				{
					if (e->dst == dst) return true;
				}
			}
			return false;
		}
		bool GetVerticeValue(int v, ValueType& value) const 
		{
			if (IsVerticeContianed(v))
			{
				value = Vertices[v]->value;
				return true;
			}
			return false;
		}
		bool GetWeight(int src, int dst, WeightType& weight) const 
		{

			if (IsVerticeContianed(src) && IsVerticeContianed(dst))
			{
				if (src == dst)
				{
					weight = 0;
					return true;
				}
				EdgePtr e = Vertices[src]->adj;
				while (e != nullptr)
				{
					if (e->dst == dst)
					{
						weight = e->weight;
						return true;
					}
					e = e->next;
				}
			}
			return false;
		}
		void RemoveVertice(int v)
		{
			if (IsVerticeContianed(v))
			{
				int size = Vertices.Size();
				EdgePtr e = Vertices[v].adj;
				//�Ƴ��Ӵ�ɾ���ڵ�����ı�
				while (e != nullptr)
				{
					EdgePtr temp = e->next;
					delete e;
					--EdgeCount;
					e = temp;
				}
				//ɾ���ڵ㣬�������λ�ò��ܶ�����
				//�������һ����ʾ�ƽڵ�Ŀ�ָ��
				delete Vertices[v];
				Vertices[v] = nullptr;
				//�Ƴ�����ɾ���ڵ�ı�
				for (int i = 0; i < size; ++i)
				{
					if (Vertices[i] != nullptr)
						remove_edge(i, v);
				}
			}
		}
		void RemoveEdge(int src, int dst)
		{
			if (IsVerticeContianed(src) && IsVerticeContianed(dst))
			{
				remove_edge(src, dst);
			}
		}
		//����ʵ�ʴ洢�Ľڵ����
		int GetVerticeCount() const { return VerticeCount; }
		//����ʵ�ʴ洢�ıߵĸ���
		int GetEdgeCount() const { return EdgeCount; }
		//����Ϊ����ڵ��Ѿ�ռ�õĿռ䣬�еĿռ䱻ռ���ˣ�
		//��ʵ���ϴ�ŵ����ƽڵ�
		int GetVerticeSize() const
		{
			return Vertices.Size();
		}
		VerticePtr GetVertice(int v) const
		{
			if (v < 0 || v >= Vertices.Size()) return nullptr;
			return Vertices[v];
		}
	private:
		void remove_edge(int src, int dst)
		{
			if (src == dst) return;
			EdgePtr e = Vertices[src]->adj;
			EdgePtr pre;
			while (e != nullptr)
			{
				pre = e;
				if (e->dst == dst)
				{
					if (e == Vertices[src]->adj)
					{
						Vertices[src]->adj = e->next;
						delete pre;
						e = Vertices[src]->adj;
					}
					else
					{
						pre->next = e->next;
						delete e;
						e = pre->next;
					}
					--EdgeCount;
				}
				else e = e->next;
			}
		}
	private:
		int VerticeCount;
		int EdgeCount;
		Vector<VerticePtr> Vertices;
	};
}
#endif