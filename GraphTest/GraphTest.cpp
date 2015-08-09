// GraphTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "../include/DirectedWeightGraph.h"
#include "../Tool/MinGenTree.h"
#include "../Tool/ShortestPath.h"
#include "../Tool/TopologicalSort.h"
#include "../Tool/GraphTraverse.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace MyDataStructure;
using namespace MyTools;
using namespace std;
bool LoadVertice(string filename, Vector<string>& citynames)
{
	ifstream input;
	citynames.Clear();
	input.open(filename);
	string city;
	int no;
	while (input>>no>>city)
	{
		citynames.PushBack(city);
	}
	input.close();
	return true;
}

bool LoadEdge(string filename, Vector<int>& srcs,Vector<int>& dsts,Vector<float>& weights)
{
	ifstream input;
	srcs.Clear();
	dsts.Clear();
	weights.Clear();
	input.open(filename);
	int src, dst;
	float weight;
	while (input>>src>>dst>>weight)
	{
		srcs.PushBack(src);
		dsts.PushBack(dst);
		weights.PushBack(weight);
	}
	input.close();
	return true;
}

void print1(const string& s)
{
	cout << "-->" << s;
}

//template<ValueType>
struct Vis
{
	Vis(string s)
	{
		this->s = s;
	}
	void operator()(const string& value)
	{
		cout <<s +  "-->" << value;
	}
private:
	string s;
};

int _tmain(int argc, _TCHAR* argv[])
{
	Vector<int> srcs,dsts;
	Vector<string> citynames;
	Vector<float> weights;
	LoadVertice("vertice - 副本.txt", citynames);
	LoadEdge("edge - 副本.txt", srcs, dsts, weights);
	DirectedWeightGraph<string, float> WG(citynames, srcs, dsts, weights);
	int verticecount = citynames.Size(), edgecount = weights.Size();
	/*for (int i = 0; i < verticecount; ++i)
	{
		string value;
		if (WG.GetVerticeValue(i, value))
			cout << value << endl;
	}
	for (int i = 0; i < edgecount; ++i)
	{
		for (int j = 0; j < edgecount; ++j)
		{
			float w;
			if (WG.GetWeight(i,j,w) && i != j)
			{
				cout << i << "---------->" << j << ":   " << w << endl;
			}
		}
	}
	cout << WG.GetVerticeCount() << endl;
	cout << WG.GetEdgeCount() << endl;*/
	/*MinGenTree<string, float> mgt;
	Vector<DirectedWeightGraph<string, float>::EdgePtr> minTree = mgt.Kruscal(WG);
	for (int i = 0; i < minTree.Size(); ++i)
	{
		cout << minTree[i]->src << "------->" << minTree[i]->dst << endl;
	}
	Vector<int> path;
	Vector<float> dist;
	Dijkstra(WG, 0, path, dist, FLT_MAX);
	for (int i = 1; i < dist.Size(); ++i)
	{
		cout << "0-------->" << i << "的距离： " << dist[i] << endl;
	}*/
	/*Vector<int> s;
	cout << TopologicalSort(WG, s) << endl;
	cout << s.Size() << endl;
	for (int i = 0; i < s.Size(); ++i)
	{
		string value;
		if (WG.GetVerticeValue(s[i], value))
			cout <<"-->" <<s[i]<<'.'<<value;
	}
	cout << endl;*/
	cout << "广度优先：" << endl;
	BFS(WG, 0, Vis("***"));
	cout << "深度优先：" << endl;
	DFS(WG, 0, print1);
	return 0;
}

