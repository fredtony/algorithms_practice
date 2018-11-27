#include <iostream>
#include <cassert>
#include <vector>
#include <queue>
#include <limits>
#include <utility>
#include <cmath>
#include <tuple>
#include <string>

using namespace std;

// See the explanations of these typedefs and constants in the starter for friend_suggestion
typedef vector<vector<vector<int>>> Adj;
typedef long long Len;
typedef vector<priority_queue<tuple<double, Len, int>,vector<tuple<double, Len,int>>,greater<tuple<double, Len,int>>>> Queue;

const Len INF = numeric_limits<Len>::max() / 4;

class AStar {
	// See the descriptions of these fields in the starter for friend_suggestion
	int n_;
	Adj adj_;
	Adj cost_;
	vector<vector<Len>> distance_;
	vector<int> workset_;
	vector<int> visited_;
	// Coordinates of the nodes
	vector<pair<Len,Len>> xy_;

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

	double get_potential(Len true_cost, pair<Len,Len> xy1, pair<Len,Len> xy2, pair<Len,Len> dest, pair<Len,Len> source) {
		double diff1 = (sqrt(pow(get<0>(dest) - get<0>(xy1), 2) + pow(get<1>(dest) - get<1>(xy1), 2))
						- sqrt(pow(get<0>(source) - get<0>(xy1), 2) + pow(get<1>(source) - get<1>(xy1), 2))) / 2;
		double diff2 = (sqrt(pow(get<0>(dest) - get<0>(xy2), 2) + pow(get<1>(dest) - get<1>(xy2), 2))
						- sqrt(pow(get<0>(source) - get<0>(xy2), 2) + pow(get<1>(source) - get<1>(xy2), 2))) / 2;
		return (double) true_cost + diff2 - diff1;
	}

public:
	AStar(int n, Adj adj, Adj cost, vector<pair<Len,Len>> xy) :
		n_(n), adj_(adj), cost_(cost), distance_(2, vector<Len>(n_, INF)), visited_(n, 0), xy_(xy)
	{ workset_.reserve(n); }

	// See the description of this method in the starter for friend_suggestion
	void clear() {
		int v;
		for (int i = 0; i < workset_.size(); ++i) {
			v = workset_[i];
			distance_[0][v] = distance_[1][v] = INF;
			visited_[v] = 0;
		}
		workset_.clear();
	}

	// See the description of this method in the starter for friend_suggestion
	void visit(Queue& q, int side, int v, Len dist, pair<Len,Len> dest, pair<Len,Len> source) {
		string tmp;
		if (side) {
			tmp = "backward";
		} else {
			tmp = "forward";
		}
		cout << "\tVisiting vertex " << v+1 << " on the " << tmp << " search." << endl;
		distance_[side][v] = dist;
		if (visited_[v] == 0) {
			visited_[v] = side + 1;
		} else {
			visited_[v] = 3;
		}
		Len new_cost;
		int next_vertex;
		double val;
		for (int i = 0; i < adj_[side][v].size(); ++i) {
			next_vertex = adj_[side][v][i];
			new_cost = dist + cost_[side][v][i];
			if (distance_[0][next_vertex] == INF && distance_[1][next_vertex] == INF) {
				workset_.push_back(next_vertex);
			}
			if (distance_[side][next_vertex] > new_cost) {
				distance_[side][next_vertex] = new_cost;
				val = get_potential(new_cost, xy_[v], xy_[next_vertex], dest, source);
				q[side].emplace(val, new_cost, next_vertex);
				cout << "\t\tAdded vertex " << next_vertex+1 << " to the " << tmp << " queue with val " << val << endl;
			}
		}
	}

	// Returns the distance from s to t in the graph
	Len query(int s, int t) {
		clear();
		Queue q(2);
		workset_.push_back(s);
		workset_.push_back(t);
		visit(q, 0, s, 0, xy_[t], xy_[s]);
		visit(q, 1, t, 0, xy_[s], xy_[t]);
		int curr_vertex;
		Len dist;
		// int counter = 0;
		while (!q[0].empty() || !q[1].empty()) {
			if (!q[0].empty()) {
				curr_vertex = get<2>(q[0].top());
				dist = get<1>(q[0].top());
				q[0].pop();
				cout << "Looking at vertex " << curr_vertex+1 << " on the forward search/" << visited_[curr_vertex] << endl;
				if (visited_[curr_vertex] == 0 || visited_[curr_vertex] == 2) {
					visit(q, 0, curr_vertex, dist, xy_[t], xy_[s]);
					if (visited_[curr_vertex] == 3) {
						return shortest_path();
					}
				}
			}
			if (!q[1].empty()) {
				curr_vertex = get<2>(q[1].top());
				dist = get<1>(q[1].top());
				q[1].pop();
				cout << "Looking at vertex " << curr_vertex+1 << " on the backward search/" << visited_[curr_vertex] << endl;
				if (visited_[curr_vertex] == 0 || visited_[curr_vertex] == 1) {
					visit(q, 1, curr_vertex, dist, xy_[s], xy_[t]);
					if (visited_[curr_vertex] == 3) {
						return shortest_path();
					}
				}
			}
		}
		return shortest_path();
	}
};

int main() {
	int n, m;
	cin >> n >> m;
	vector<pair<Len,Len>> xy(n);
	for (int i=0;i<n;++i){
		int a, b;
		cin >> a >> b;
		xy[i] = make_pair(a,b);
	}
	Adj adj(2, vector<vector<int>>(n));
	Adj cost(2, vector<vector<int>>(n));
	int u, v, c;
	for (int i = 0; i < m; ++i) {
		cin >> u >> v >> c;
		adj[0][u-1].push_back(v-1);
		cost[0][u-1].push_back(c);
		adj[1][v-1].push_back(u-1);
		cost[1][v-1].push_back(c);
	}

	AStar astar(n, adj, cost, xy);

	int t;
	cin >> t;
	for (int i = 0; i < t; ++i) {
		int u, v;
		cin >> u >> v;
		cout << astar.query(u-1, v-1) << endl;
	}
	return 0;
}
