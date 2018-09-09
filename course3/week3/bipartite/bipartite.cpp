#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int bipartite(vector<vector<int> > &adj) {
	vector<int> white(adj.size(), false);
	vector<bool> used(adj.size(), false);
	queue<int> vertex_queue;
	int curr_vertex, next_vertex;
	for (int i = 0; i < adj.size(); ++i) {
		if (!used[i]) {
			vertex_queue.push(i);
			used[i] = true;
			white[i] = 1;
			while (!vertex_queue.empty()) {
				curr_vertex = vertex_queue.front();
				vertex_queue.pop();
				for (int j = 0; j < adj[curr_vertex].size(); ++j) {
					next_vertex = adj[curr_vertex][j];
					if (used[next_vertex] && white[next_vertex] != 1 - white[curr_vertex]) {
						return 0;
					} else if (!used[next_vertex]) {
						vertex_queue.push(next_vertex);
						used[next_vertex] = true;
						white[next_vertex] = 1 - white[curr_vertex];
					}
				}
			}
		}
	}
	return 1;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj[y - 1].push_back(x - 1);
	}
	std::cout << bipartite(adj);
}
