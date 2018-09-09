#include <iostream>
#include <vector>
#include <queue>
#include <functional>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;
using std::get;

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
	vector<bool> in_set(adj.size(), false);
	vector<int> dist(adj.size(), -1);
	priority_queue<pair<int, int>, vector<pair<int, int>>, std::greater<pair<int, int>>> vertex_heap;
	vertex_heap.emplace(0, s);
	int curr_vertex, next_vertex;
	while (!vertex_heap.empty()) {
		// std::cout << "Size of heap: " << vertex_heap.size() << std::endl;
		curr_vertex = get<1>(vertex_heap.top());
		if (curr_vertex == t) {
			return get<0>(vertex_heap.top());
		}
		if (!in_set[curr_vertex]) {
			dist[curr_vertex] = get<0>(vertex_heap.top());
			in_set[curr_vertex] = true;
			for (int i = 0; i < adj[curr_vertex].size(); ++i) {
				next_vertex = adj[curr_vertex][i];
				if (!in_set[next_vertex]) {
					vertex_heap.emplace(dist[curr_vertex] + cost[curr_vertex][i], next_vertex);
				}
			}
		}
		vertex_heap.pop();
	}
	return -1;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	vector<vector<int> > cost(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}
	int s, t;
	std::cin >> s >> t;
	s--, t--;
	std::cout << distance(adj, cost, s, t);
}
