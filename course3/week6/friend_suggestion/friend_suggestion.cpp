#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>

using namespace std;

// External vector of size 2 - for forward and backward search.
// Internal 2-dimensional vector is vector of adjacency lists for each node.
typedef vector<vector<vector<int>>> Adj;

// Distances can grow out of int type
typedef long long Len;

// Vector of two priority queues - for forward and backward searches.
// Each priority queue stores the closest unprocessed node in its head.
typedef vector<priority_queue<pair<Len, int>,vector<pair<Len,int>>,greater<pair<Len,int>>>> Queue;

const Len INF = (Len)(numeric_limits<Len>::max() / 4);

class Bidijkstra {
	// Number of nodes
	int n_;
	// Graph adj_[0] and cost_[0] correspond to the initial graph,
	// adj_[1] and cost_[1] correspond to the reversed graph.
	// Graphs are stored as vectors of adjacency lists corresponding
	// to nodes.
	// Adjacency list itself is stored in adj_, and the corresponding
	// edge costs are stored in cost_.
	Adj adj_;
	Adj cost_;
	// distance_[0] stores distances for the forward search,
	// and distance_[1] stores distances for the backward search.
	vector<vector<Len>> distance_;
	// Stores all the nodes visited either by forward or backward search.
	vector<int> workset_;
	// Stores a flag for each node which is 0 if not visited at all yet, 1
	// if visited by forward search only, 2 if visited by backward search only,
	// and 3 if visited by both forward and backward search
	vector<int> visited_;

	// Finds shortest path from s to t once the distances are built
	Len shortest_path() {
		Len result = INF;
		for (int i = 0; i < workset_.size(); ++i) {
			if (distance_[0][workset_[i]] + distance_[1][workset_[i]] < result) {
				result = distance_[0][workset_[i]] + distance_[1][workset_[i]];
			}
		}
		if (result == INF)
			return -1;
		return result;
	}

public:
	Bidijkstra(int n, Adj adj, Adj cost) : n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n, INF)), visited_(n)
	{ workset_.reserve(n); }

	// Initialize the data structures before new query,
	// clear the changes made by the previous query.
	void clear() {
		int v;
		for (int i = 0; i < workset_.size(); ++i) {
			v = workset_[i];
			distance_[0][v] = distance_[1][v] = INF;
			visited_[v] = 0;
		}
		workset_.clear();
	}

	// Processes visit of either forward or backward search 
	// (determined by value of side), to node v trying to
	// relax the current distance by dist.
	void visit(Queue& q, int side, int v, Len dist) {
		distance_[side][v] = dist;
		if (visited_[v] == 0) {
			visited_[v] = side + 1;
		} else {
			visited_[v] = 3;
		}
		Len new_cost;
		int next_vertex;
		for (int i = 0; i < adj_[side][v].size(); ++i) {
			next_vertex = adj_[side][v][i];
			new_cost = dist + cost_[side][v][i];
			if (distance_[0][next_vertex] == INF && distance_[1][next_vertex] == INF) {
				workset_.push_back(next_vertex);
			}
			if (distance_[side][next_vertex] > new_cost) {
				distance_[side][next_vertex] = new_cost;
				q[side].emplace(new_cost, next_vertex);
			}
		}
	}

	// Returns the distance from s to t in the graph.
	Len query(int s, int t) {
		clear();
		Queue q(2);
		workset_.push_back(s);
		workset_.push_back(t);
		visit(q, 0, s, 0);
		visit(q, 1, t, 0);
		int curr_vertex;
		// int counter = 0;
		while (!q[0].empty() || !q[1].empty()) {
			if (!q[0].empty()) {
				curr_vertex = get<1>(q[0].top());
				if (visited_[curr_vertex] == 0 || visited_[curr_vertex] == 2) {
					visit(q, 0, curr_vertex, get<0>(q[0].top()));
					if (visited_[curr_vertex] == 3) {
						return shortest_path();
					}
				}
				q[0].pop();
			}
			if (!q[1].empty()) {
				curr_vertex = get<1>(q[1].top());
				if (visited_[curr_vertex] == 0 || visited_[curr_vertex] == 1) {
					visit(q, 1, curr_vertex, get<0>(q[1].top()));
					if (visited_[curr_vertex] == 3) {
						return shortest_path();
					}
				}
				q[1].pop();
			}
		}
		return shortest_path();
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	Adj adj(2, vector<vector<int>>(n));
	Adj cost(2, vector<vector<int>>(n));
	for (int i=0; i<m; ++i) {
		int u, v, c;
		cin >> u >> v >> c;
		adj[0][u-1].push_back(v-1);
		cost[0][u-1].push_back(c);
		adj[1][v-1].push_back(u-1);
		cost[1][v-1].push_back(c);
	}

	Bidijkstra bidij(n, adj, cost);

	int t, u, v;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		cin >> u >> v;
		cout << bidij.query(u-1, v-1) << endl;
	}
}
