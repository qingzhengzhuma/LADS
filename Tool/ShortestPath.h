#ifndef _SHORTESTPATH_H_
#define _SHORTESTPATH_H_

#include "../include/DirectedWeightGraph.h"
#include "../include/Vector.h"
using namespace MyDataStructure;

namespace MyTools
{
	template<typename ValueType, typename WeightType>
	void Dijkstra(const DirectedWeightGraph<ValueType, WeightType>& Graph, int v,Vector<int>& path,Vector<WeightType>& dist, WeightType maxValue)
	{
		int size = Graph.GetVerticeSize();
		Vector<bool> S(size);
		dist.Resize(size);
		path.Resize(size);
		for (int i = 0; i < size; ++i)
		{
			dist.PushBack(maxValue);
			Graph.GetWeight(v, i, dist[i]);
			S.PushBack(false);
			if (i != v && dist[i] < maxValue) path.PushBack(v);
			else path.PushBack(-1);
		}
		S[v] = true;
		dist[v] = 0;
		for (int i = 0; i < size - 1; ++i)
		{
			WeightType min = maxValue;
			int u = v;
			for (int j = 0; j < size; ++j)
			{
				if (S[j] != true && dist[j] < min)
				{
					min = dist[j];
					u = j;
				}
			}
			S[u] = true;
			for (int j = 0; j < size; ++j)
			{
				WeightType w = maxValue;
				Graph.GetWeight(u, j, w);
				if (S[j] != true && w < maxValue && dist[u] + w < dist[j])
				{
					dist[j] = dist[u] + w;
					path[j] = u;
				}
			}
		}
	}
}

#endif