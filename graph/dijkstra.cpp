#include <bits/stdc++.h>
using namespace std;

template <typename T>
class Graph
{
	unordered_map <T, list<pair<T, int> > > m;
public:
	void add_edge(T x, T y, int d, bool b = true)
	{
		m[x].push_back(make_pair(y, d));
		if(b)
		{
			m[y].push_back(make_pair(x, d));
		}
	}

	void print_adj_list()
	{
		for(auto c : m)
		{
			cout << c.first << "->";
			for(auto n : c.second)
			{
				cout << "(" << n.first << ", " << n.second << ") ";
			}
			cout << endl;
		}
	}

	void dijkstra(T source)
	{
		unordered_map <T, int> distance; //key - node and value - distance from source
		for(auto c : m) // O(V)
			distance[c.first] = INT_MAX;
		distance[source] = 0;
		set <pair <int, T> > s; //set is always ordered, in this case it will be ordered on the basis of distance (the first parameter) //op of retrieval of top is o(1), removal is o(logn)
		s.insert(make_pair(0, source));

		while (!s.empty()) // O(V)
		{
			auto p = *(s.begin()); // minimum distance node
			T node = p.second;
			int node_distance = p.first;

			s.erase(s.begin()); // O(log V)

			for(auto child_pair : m[node]) // O(logV) * V
			{
				if(node_distance + child_pair.second < distance[child_pair.first])
				{
					T destination = child_pair.first;
					auto f = s.find(make_pair(distance[destination], destination));
					if(f != s.end())
					{
						s.erase(f);
					}
					distance[destination] = node_distance + child_pair.second;
					s.insert(make_pair(distance[destination], destination));

				}
			}

		}

		for(auto d : distance)
		{
			cout << d.first << " is located at a distance of " << d.second << " from the source" << endl;
		}


	}

};

int main()
{
	Graph <string> g;
	g.add_edge("A", "B", 1);
	g.add_edge("A", "C", 4);
	g.add_edge("C", "B", 2);
	g.add_edge("C", "D", 8);
	g.add_edge("E", "F", 2);
	g.add_edge("D", "E", 3);
	g.add_edge("F", "B", 1);

	g.dijkstra("A");
	return 0;
}