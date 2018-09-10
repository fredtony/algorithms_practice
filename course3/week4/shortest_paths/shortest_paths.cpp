#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

#define INF std::numeric_limits<long long>::max()

void relax(vector<int> &prev, vector<long long> &dist, int u, int v, int weight) {
	if (dist[u] != INF && dist[v] > dist[u] + weight) {
		dist[v] = dist[u] + weight;
		prev[v] = u;
	}
}

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &distance, vector<int> &reachable, vector<int> &shortest) {
	vector<int> prev(adj.size(), -1);
	distance[s] = 0;
	for (int i = 0; i < adj.size() - 1; ++i) {
		for (int j = 0; j < adj.size(); ++j) {
			for (int k = 0; k < adj[j].size(); ++k) {
				relax(prev, distance, j, adj[j][k], cost[j][k]);
			}
		}
	}
	queue<int> in_neg_cycles;
	for (int j = 0; j < adj.size(); ++j) {
		if (distance[j] < std::numeric_limits<long long>:: max()) {
			reachable[j] = 1;
		}
		for (int k = 0; k < adj[j].size(); ++k) {
			if (distance[j] != INF && distance[adj[j][k]] > distance[j] + cost[j][k]) {
				in_neg_cycles.push(adj[j][k]);
			}
		}
	}
	int curr_vertex, next_vertex;
	while (!in_neg_cycles.empty()) {
		curr_vertex = in_neg_cycles.front();
		shortest[curr_vertex] = 0;
		in_neg_cycles.pop();
		for (int i = 0; i < adj[curr_vertex].size(); ++i) {
			next_vertex = adj[curr_vertex][i];
			if (shortest[next_vertex]) {
				shortest[next_vertex] = 0;
				in_neg_cycles.push(next_vertex);
			}
		}
	}
}

int main() {
	int n, m, s;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	vector<vector<int> > cost(n, vector<int>());
	for (int i = 0; i < m; i++) {
		int x, y, w;
		std::cin >> x >> y >> w;
		adj[x - 1].push_back(y - 1);
		cost[x - 1].push_back(w);
	}
	std::cin >> s;
	s--;
	vector<long long> distance(n, INF);
	vector<int> reachable(n, 0);
	vector<int> shortest(n, 1);
	shortest_paths(adj, cost, s, distance, reachable, shortest);
	for (int i = 0; i < n; i++) {
		if (!reachable[i]) {
			std::cout << "*\n";
		} else if (!shortest[i]) {
			std::cout << "-\n";
		} else {
			std::cout << distance[i] << "\n";
		}
	}
}
