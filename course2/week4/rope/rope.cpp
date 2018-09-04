#include <cstdio>
#include <string>
#include <iostream>

bool debug = false;

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
	char key;
	// Rank in the subtree - remember to update
	// it after each operation that changes the tree.
	long long size;
	Vertex* left;
	Vertex* right;
	Vertex* parent;

	Vertex(char key) : key(key), size(1), left(NULL), right(NULL), parent(NULL) {}
};

void printTree(struct Vertex* curr, int depth);
void printTree(struct Vertex* curr);

void update(Vertex* v) {
	if (v == NULL) return;
	v->size = 1 + (v->left != NULL ? v->left->size : 0ll) + (v->right != NULL ? v->right->size : 0ll);
	if (v->left != NULL) {
		v->left->parent = v;
	}
	if (v->right != NULL) {
		v->right->parent = v;
	}
}

void small_rotation(Vertex* v) {
	Vertex* parent = v->parent;
	if (parent == NULL) {
		return;
	}
	Vertex* grandparent = v->parent->parent;
	if (parent->left == v) {
		Vertex* m = v->right;
		v->right = parent;
		parent->left = m;
	} else {
		Vertex* m = v->left;
		v->left = parent;
		parent->right = m;
	}
	update(parent);
	update(v);
	v->parent = grandparent;
	if (grandparent != NULL) {
		if (grandparent->left == parent) {
			grandparent->left = v;
		} else {
			grandparent->right = v;
		}
	}
}

void big_rotation(Vertex* v) {
	if (v->parent->left == v && v->parent->parent->left == v->parent) {
		// Zig-zig
		small_rotation(v->parent);
		small_rotation(v);
	} else if (v->parent->right == v && v->parent->parent->right == v->parent) {
		// Zig-zig
		small_rotation(v->parent);
		small_rotation(v);
	} else {
		// Zig-zag
		small_rotation(v);
		small_rotation(v);
	}
}

// Makes splay of the given vertex and makes
// it the new root.
void splay(Vertex*& root, Vertex* v) {
	if (v == NULL) return;
	while (v->parent != NULL) {
		if (v->parent->parent == NULL) {
			small_rotation(v);
			break;
		}
		big_rotation(v);
	}
	root = v;
}

// Find the vertex with rank "rank".
// If the key is bigger than the size of the tree, 
// returns NULL.
Vertex* find(Vertex*& node, int rank) {
	long long size;
	if (node == NULL || rank > node->size - 1) return NULL;
	if (node->left == NULL) {
		size = 0;
	} else {
		size = node->left->size;
	}
	if (rank == size) {
		return node;
	} else if (rank < size) {
		return find(node->left, rank);
	} else {
		return find(node->right, rank - size - 1); // ?
	}
}

void split(Vertex* root, int rank, Vertex*& left, Vertex*& right) {
	right = find(root, rank);
	splay(root, right);
	if (right == NULL) {
		left = root;
		return;
	}
	left = right->left;
	right->left = NULL;
	if (left != NULL) {
		left->parent = NULL;
	}
	update(left);
	update(right);
}

Vertex* merge(Vertex* left, Vertex* right) {
	if (left == NULL) return right;
	if (right == NULL) return left;
	Vertex* min_right = right;
	while (min_right->left != NULL) {
		min_right = min_right->left;
	}
	splay(right, min_right);
	right->left = left;
	update(right);
	return right;
}

void postorder(Vertex* node) {
	if (node != NULL) {
		postorder(node->left);
		std::cout << node->key;
		postorder(node->right);
	}
}

class Rope {
	Vertex* root;
public:
	Rope(const std::string &s) : root(NULL) {
		Vertex* new_vertex;
		for (int i = 0; i < s.size(); ++i) {
			new_vertex = new Vertex(s[i]);
			root = merge(root, new_vertex);
		}
		Vertex* middle_node = find(root, s.size() / 2);
		splay(root, middle_node);
		if (debug) printTree(root);
	}

	void process(int i, int j, int k) {
		Vertex* left = NULL;
		Vertex* tmp_right = NULL;
		Vertex* middle = NULL;
		Vertex* right = NULL;
		split(root, i, left, tmp_right);
		if (debug) {
			std::cout << "Left:\n";
				printTree(left);
			std::cout << "Temp right:\n";
			printTree(tmp_right);
		}
		split(tmp_right, j - i + 1, middle, right);
		if (debug) {
			std::cout << "Middle:\n";
			printTree(middle);
			std::cout << "Right:\n";
			printTree(right);
		}
		root = merge(left, right);
		if (debug) {
			std::cout << "Back together (before splice):\n";
			printTree(root);
		}
		split(root, k, left, right);
		if (debug) {
			std::cout << "New Left:\n";
			printTree(left);
			std::cout << "New Right:\n";
			printTree(right);
		}
		root = merge(left, merge(middle, right));
		if (debug) {
			std::cout << "Recombined:\n";
			printTree(root);
		}
	}

	void result() {
		if (debug) printTree(root);
		postorder(root);
	}
};

// class naiveRope {
// 	std::string s;
// public:
// 	Rope(std::string & s) : s(s) {}

// 	void process(int i, int j, int k) {
// 		// Replace this code with a faster implementation
// 		std::string t = s.substr(0, i) + s.substr(j + 1);
// 		s = t.substr(0, k) + s.substr(i, j - i + 1) + t.substr(k);
// 	}

// 	std::string result() {
// 		return s;
// 	}
// };

const int MODULO = 1000000001;

int rec[1000006];
void printTree(struct Vertex* curr, int depth) {
	int i;
	if (curr == NULL) return;
	std::cout << "\t";
	std::string tmp_str;
	for(i = 0; i < depth; i++) {
		if(i == depth - 1) {
			tmp_str = rec[depth-1] ? "+" : "L";
			std::cout << tmp_str << "---";
		} else {
			tmp_str = rec[i] ? "|" : "  ";
			std::cout << tmp_str << "   ";
		}
	}
	std::cout << curr->key << "/" << curr->size << "\n";
	rec[depth] = 1;
	printTree(curr->left, depth + 1);
	rec[depth] = 0;
	printTree(curr->right, depth + 1);
}

void printTree(struct Vertex* curr) {
	printTree(curr, 0);
	std::cout << "\n";
}

int main() {
	std::ios_base::sync_with_stdio(0);
	std::string s;
	std::cin >> s;
	Rope rope(s);
	int actions;
	std::cin >> actions;
		for (int action_index = 0; action_index < actions; ++action_index) {
			int i, j, k;
		std::cin >> i >> j >> k;
		rope.process(i, j, k);
	}
	rope.result();
	std::cout << std::endl;
}
