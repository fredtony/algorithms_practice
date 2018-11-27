#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>
#include <tuple>

using std::vector;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(): size(0), parent(-1), rank(0) {}
};

struct DisjointSets {
	int size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int vertex) {
		if (sets[vertex].parent == vertex)
			return vertex;
		int par = sets[vertex].parent;
		if (sets[par].parent == par)
			return par;
		else {
			sets[vertex].parent = getParent(par);
			return sets[vertex].parent;
		}
	}

	void merge(int destination, int source) {
		int realDestination = getParent(destination);
		int realSource = getParent(source);
		int parent, child;
		if (realDestination != realSource) {
			if (sets[realSource].rank > sets[realDestination].rank) {
				parent = realSource;
				child = realDestination;
			}
			else {
				parent = realDestination;
				child = realSource;
			}
			if (parent == child) {
				sets[parent].rank++;
			}
			sets[parent].size += sets[child].size;
			sets[child].parent = parent;
		}		
	}
};

double minimum_distance(vector<int> x, vector<int> y) {
	double result = 0.;
	std::priority_queue<std::tuple<double, int, int>, vector<std::tuple<double, int, int>>, std::greater<std::tuple<double, int, int>>> distances;
	DisjointSets vertices = DisjointSets(x.size());
	for (int i = 0; i < x.size() - 1; ++i) {
		for (int j = i + 1; j < x.size(); ++j) {
			distances.emplace(std::sqrt(std::pow(x[i] - x[j], 2) + std::pow(y[i] - y[j], 2)), i, j);
		}
	}
	int source, destination;
	while (!distances.empty()) {
		source = std::get<1>(distances.top());
		destination = std::get<2>(distances.top());
		if (vertices.getParent(source) != vertices.getParent(destination)) {
			result += std::get<0>(distances.top());
			vertices.merge(source, destination);
		}
		distances.pop();
	}
	return result;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<int> x(n), y(n);
	for (size_t i = 0; i < n; i++) {
		std::cin >> x[i] >> y[i];
	}
	std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
