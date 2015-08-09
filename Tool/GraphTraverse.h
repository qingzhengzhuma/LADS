#ifndef _GRAPHTRAVERSE_H_
#define _GRAPHTRAVERSE_H_

#include "../include/DirectedWeightGraph.h"
#include <queue>

using namespace MyDataStructure;
using namespace std;

namespace MyTools
{
	template<typename Value, typename Weight, typename Visitor>
	struct bfs
	{
		void operator()(DirectedWeightGraph<Value, Weight>& Graph, int v, Vector<bool>& is_visited,Visitor vf)
		{
			typedef DirectedWeightGraph<Value, Weight>::VerticePtr VerticePtr;
			typedef DirectedWeightGraph<Value, Weight>::EdgePtr EdgePtr;
			if (is_visited[v] == true) return;
			queue<int> q;
			q.push(v);
			while (q.empty() != true)
			{
				int v1 = q.front();
				if (is_visited[v1] != true && Graph.IsVerticeContianed(v1))
				{
					VerticePtr v_ptr = Graph.GetVertice(v1);
					vf(v_ptr->value);
					is_visited[v1] = true;
					EdgePtr e = v_ptr->adj;
					while (e != nullptr)
					{
						if (is_visited[e->dst] != true)
						{
							q.push(e->dst);
						}
						e = e->next;
					}
				}
				q.pop();
			}
		}
	};
	template<typename Value, typename Weight, typename Visitor>
	struct dfs
	{
		void operator()(DirectedWeightGraph<Value, Weight>& Graph, int v, Vector<bool>& is_visited,Visitor vf)
		{
			typedef DirectedWeightGraph<Value, Weight>::VerticePtr VerticePtr;
			typedef DirectedWeightGraph<Value, Weight>::EdgePtr EdgePtr;
			if (Graph.IsVerticeContianed(v) && is_visited[v] != true)
			{
				VerticePtr v_ptr = Graph.GetVertice(v);
				vf(v_ptr->value);
				is_visited[v] = true;
				EdgePtr e = v_ptr->adj;
				while (e != nullptr)
				{
					if (is_visited[e->dst] != true)
					{
						operator()(Graph,e->dst, is_visited, vf);
					}
					e = e->next;
				}
			}
		}
	};

	template<typename Value, typename Weight,typename TraverseMethod, typename Visitor>
	bool Traverse(DirectedWeightGraph<Value, Weight>& Graph,int start,TraverseMethod tm, Visitor vf)
	{
		if (Graph.IsVerticeContianed(start) == true)
		{
			int size = Graph.GetVerticeSize();
			Vector<bool> visited(size);
			for (int i = 0; i < size; ++i)
			{
				visited[i] = false;
			}
			for (int i = 0; i < size; ++i)
			{
				int v = start++ % size;
				if (visited[v] == false)
				{
					tm(Graph,v, visited, vf);
					cout << endl;
				}
			}
			return true;
		}
		return false;
	}
	template<typename Value, typename Weight,typename Visitor>
	bool BFS(DirectedWeightGraph<Value,Weight>& Graph, int start,Visitor vf)
	{
		bfs<Value, Weight, Visitor> b;
		return Traverse(Graph, start, b, vf);
	}
	template<typename Value, typename Weight,typename Visitor>
	bool DFS(DirectedWeightGraph<Value, Weight>& Graph, int start, Visitor vf)
	{
		dfs<Value, Weight, Visitor> d;
		return Traverse(Graph, start, d, vf);
	}
}



#endif