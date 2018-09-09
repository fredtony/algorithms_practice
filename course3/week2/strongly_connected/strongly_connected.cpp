#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void dfs(vector<vector<int> > &adj, vector<bool> &used, vector<int> &order, int x, bool add_order) {
	used[x] = true;
	for (int i = 0; i < adj[x].size(); ++i) {
		if (!used[adj[x][i]]) {
			dfs(adj, used, order, adj[x][i], add_order);
		}
	}
	if (add_order) {
		order.push_back(x);
	}
}

int number_of_strongly_connected_components(vector<vector<int> > adj, vector<vector<int> > adj_rev) {
	int result = 0;
	vector<bool> used(adj_rev.size(), false);
	vector<int> order;
	for (int i = 0; i < adj_rev.size(); ++i) {
		if (!used[i]) {
			dfs(adj_rev, used, order, i, true);
		}
	}
	std::reverse(order.begin(), order.end());
	for (int i = 0; i < used.size(); ++i) {
		used[i] = false;
	}
	for (int i = 0; i < order.size(); ++i) {
		if (!used[order[i]]) {
			result++;
			dfs(adj, used, order, order[i], false);
		}
	}
	return result;
}

int main() {
	size_t n, m;
	std::cin >> n >> m;
	vector<vector<int> > adj(n, vector<int>());
	vector<vector<int> > adj_rev(n, vector<int>());
	for (size_t i = 0; i < m; i++) {
		int x, y;
		std::cin >> x >> y;
		adj[x - 1].push_back(y - 1);
		adj_rev[y - 1].push_back(x - 1);
	}
	std::cout << number_of_strongly_connected_components(adj, adj_rev);
}
