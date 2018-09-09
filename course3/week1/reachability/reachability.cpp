#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::pair;
using std::queue;


int reach(vector<vector<int> > &adj, int x, int y) {
	vector<bool> checked(adj.size());
	queue<int> vertex_queue;
	vertex_queue.push(x);
	checked[x] = true;
	int curr_vertex, next_vertex;
	while (!vertex_queue.empty()) {
		curr_vertex = vertex_queue.front();
		vertex_queue.pop();
		for (int i = 0; i < adj[curr_vertex].size(); ++i) {
			next_vertex = adj[curr_vertex][i];
			if (next_vertex == y) {
				return 1;
			} else if (!checked[next_vertex]) {
				vertex_queue.push(next_vertex);
				checked[next_vertex] = true;
			}
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
		adj[y - 1].push_back(x - 1);
	}
	int x, y;
	std::cin >> x >> y;
	std::cout << reach(adj, x - 1, y - 1);
}
