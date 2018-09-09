#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::pair;
using std::queue;


bool connect(vector<vector<int> > &adj, int x) {
	int curr_vertex, next_vertex;
	vector<bool> checked(adj.size());
	queue<int> vertex_queue;
	vertex_queue.push(x);
	checked[x] = true;
	while (!vertex_queue.empty()) {
		curr_vertex = vertex_queue.front();
		vertex_queue.pop();
		for (int i = 0; i < adj[curr_vertex].size(); ++i) {
			next_vertex = adj[curr_vertex][i];
			if (next_vertex == x) {
				return true;
			} else if (!checked[next_vertex]) {
				vertex_queue.push(next_vertex);
				checked[next_vertex] = true;
			}
		}
	}
	return false;
}

int acyclic(vector<vector<int> > &adj) {
	for (int i = 0; i < adj.size(); ++i) {
		if (connect(adj, i)) {
			return 1;
		}
	}
	return 0;
}

int main() {
	size_t n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (size_t i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
	}
	std::cout << acyclic(adj);
}
