#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::pair;
using std::queue;

void connect(vector<vector<int> > &adj, vector<bool> &checked, queue<int> &vertex_queue) {
	int curr_vertex, next_vertex;
	while (!vertex_queue.empty()) {
		curr_vertex = vertex_queue.front();
		vertex_queue.pop();
		for (int i = 0; i < adj[curr_vertex].size(); ++i) {
			next_vertex = adj[curr_vertex][i];
			if (!checked[next_vertex]) {
				vertex_queue.push(next_vertex);
				checked[next_vertex] = true;
			}
		}
	}
}

int number_of_components(vector<vector<int> > &adj) {
	int res = 0;
	vector<bool> checked(adj.size());
	queue<int> vertex_queue;
	int curr_vertex, next_vertex;
	for (int i = 0; i < checked.size(); ++i) {
		if (!checked[i]) {
			res++;
			vertex_queue.push(i);
			connect(adj, checked, vertex_queue);
		}
	}
	return res;
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
	std::cout << number_of_components(adj);
}
