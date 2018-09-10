#include <iostream>
#include <vector>

using std::vector;

#define INFINITY 5000000

void relax(vector<int> &prev, vector<int> &dist, int u, int v, int weight) {
	if (dist[v] > dist[u] + weight) {
		dist[v] = dist[u] + weight;
		prev[v] = u;
	}
}

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
	vector<int> prev(adj.size(), -1);
	vector<int> dist(adj.size(), INFINITY);
	dist[0] = 0;
	for (int i = 0; i < adj.size() - 1; ++i) {
		for (int j = 0; j < adj.size(); ++j) {
			for (int k = 0; k < adj[j].size(); ++k) {
				relax(prev, dist, j, adj[j][k], cost[j][k]);
			}
		}
	}
	for (int j = 0; j < adj.size(); ++j) {
		for (int k = 0; k < adj[j].size(); ++k) {
			if (dist[adj[j][k]] > dist[j] + cost[j][k]) {
				return 1;
			}
		}
	}
	return 0;
}

int main() {
	int n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	vector<vector<int> > cost(n, vector<int>());
	for (int i = 0; i < m; ++i) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}
	std::cout << negative_cycle(adj, cost);
}
