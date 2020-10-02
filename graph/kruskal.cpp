#include <bits/stdc++.h>
using namespace std;

class DSU
{
	int *parent;
	int *rank;
public:
	DSU(int n)
	{
		parent = new int[n];
		rank = new int[n];

		for(int i = 0; i < n; i++)
		{
			parent[i] = -1;
			rank[i] = 1;
		}
	}

	int find(int x)
	{
		if(parent[x] == -1)
			return x;
		return parent[x] = find(parent[x]);
	}

	void unite(int x, int y)
	{
		int s1 = find(x);
		int s2 = find(y);

		if(s1 != s2)
		{
			if(rank[s1] < rank[s2])
			{
				parent[s1] = s2;
				rank[s2] += s1;
			}
			else
			{
				parent[s2] = s1;
				rank[s1] += s2;
			}
		}
	}

};


class Graph
{
	vector <vector <int> > edge_list;
	int V;
public:
	Graph(int V)
	{
		this -> V = V;
	}

	void add_edge(int x, int y, int w)
	{
		edge_list.push_back({w, x, y});
	}

	int kurskal()
	{
		int ans = 0;
		sort(edge_list.begin(), edge_list.end());
		DSU s(V);
		for(auto edge : edge_list)
		{
			int w = edge[0];
			int x = edge[1];
			int y = edge[2];

			if(s.find(x) != s.find(y))
			{
				s.unite(x, y);
				ans += w;
			}
		}
		return ans;
	}
};

int main()
{
	Graph g(4);
	g.add_edge(0, 1, 1);
	g.add_edge(1, 3, 3);
	g.add_edge(3, 2, 4);
	g.add_edge(2, 0, 2);
	g.add_edge(0, 3, 2);
	g.add_edge(1, 2, 2);

	cout << g.kurskal() << endl;
	return 0;
}