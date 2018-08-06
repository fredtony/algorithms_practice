#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

struct DisjointSetsElement {
	int size, parent, rank;
	
	DisjointSetsElement(int size = 0, int parent = -1, int rank = 0):
	    size(size), parent(parent), rank(rank) {}
};

struct DisjointSets {
	int size;
	int max_table_size;
	vector <DisjointSetsElement> sets;

	DisjointSets(int size): size(size), max_table_size(0), sets(size) {
		for (int i = 0; i < size; i++)
			sets[i].parent = i;
	}

	int getParent(int table) {
		if (sets[table].parent == table)
			return table;
		int par = sets[table].parent;
		if (sets[par].parent == par)
			return par;
		else {
			sets[table].parent = getParent(par);
			return sets[table].parent;
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
			max_table_size = max(max_table_size, sets[parent].size);
			sets[child].parent = parent;
		}		
	}
};

int main() {
	int n, m;
	cin >> n >> m;

	DisjointSets tables(n);
	for (auto &table : tables.sets) {
		cin >> table.size;
		tables.max_table_size = max(tables.max_table_size, table.size);
	}

	for (int i = 0; i < m; i++) {
		int destination, source;
		cin >> destination >> source;
        --destination;
        --source;
		
		tables.merge(destination, source);
	    cout << tables.max_table_size << endl;
	}

	return 0;
}
