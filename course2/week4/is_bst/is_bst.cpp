#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

struct Node {
	long long key;
	long long left;
	long long right;

	Node() : key(0), left(-1), right(-1) {}
	Node(long long key_, long long left_, long long right_) : key(key_), left(left_), right(right_) {}
};

bool IsBranchBinarySearchTree(const vector<Node>& tree, long long branch) {
	if (tree[branch].left != -1) {
		if (tree[tree[branch].left].key >= tree[branch].key or not IsBranchBinarySearchTree(tree, tree[branch].left))
			return false;
		long long max_check = tree[branch].left;
		while (tree[max_check].right != -1) {
			if (tree[tree[max_check].right].key >= tree[branch].key)
				return false;
			max_check = tree[max_check].right;
		}
	}
	if (tree[branch].right != -1) {
		if (tree[branch].key >= tree[tree[branch].right].key or not IsBranchBinarySearchTree(tree, tree[branch].right))
			return false;
		long long min_check = tree[branch].right;
		while (tree[min_check].left != -1) {
			if (tree[tree[min_check].left].key <= tree[branch].key)
				return false;
			min_check = tree[min_check].left;
		}
	}
	return true;
}

bool IsBinarySearchTree(const vector<Node>& tree) {
	return tree.size() == 0 or IsBranchBinarySearchTree(tree, 0);
}

int main() {
	long long nodes;
	cin >> nodes;
	vector<Node> tree;
	for (int i = 0; i < nodes; ++i) {
		long long key, left, right;
		cin >> key >> left >> right;
		tree.push_back(Node(key, left, right));
	}
	if (IsBinarySearchTree(tree))
		cout << "CORRECT" << endl;
	else
		cout << "INCORRECT" << endl;
	return 0;
}