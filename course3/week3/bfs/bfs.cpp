#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
	vector<int> dist(adj.size(), adj.size());
	vector<bool> used(adj.size(), false);
	queue<int> vertex_queue;
	vertex_queue.push(s);
	used[s] = true;
	dist[s] = 0;
	int curr_vertex, next_vertex;
	while (!vertex_queue.empty()) {
		curr_vertex = vertex_queue.front();
		vertex_queue.pop();
		for (int i = 0; i < adj[curr_vertex].size(); ++i) {
			next_vertex = adj[curr_vertex][i];
			if (next_vertex == t) {
				return dist[curr_vertex] + 1;
			} else if (!used[next_vertex]) {
				vertex_queue.push(next_vertex);
				used[next_vertex] = true;
				dist[next_vertex] = dist[curr_vertex] + 1;
			}
		}
	}
	return -1;
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
	int s, t;
	std::cin >> s >> t;
	s--, t--;
	std::cout << distance(adj, s, t);
}
