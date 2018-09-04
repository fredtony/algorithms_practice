// #include <cstdio>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std:: string;

// Splay tree implementation

// Vertex of a splay tree
struct Vertex {
	int key;
	// Sum of all the keys in the subtree - remember to update
	// it after each operation that changes the tree.
	long long sum;
	Vertex* left;
	Vertex* right;
	Vertex* parent;

	Vertex(int key, long long sum, Vertex* left, Vertex* right, Vertex* parent) 
	: key(key), sum(sum), left(left), right(right), parent(parent) {}
};

void printTree(struct Vertex* curr, int depth);

void update(Vertex* v) {
	if (v == NULL) return;
	v->sum = v->key + (v->left != NULL ? v->left->sum : 0ll) + (v->right != NULL ? v->right->sum : 0ll);
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

// Searches for the given key in the tree with the given root
// and calls splay for the deepest visited node after that.
// If found, returns a pointer to the node with the given key.
// Otherwise, returns a pointer to the node with the smallest
// bigger key (next value in the order).
// If the key is bigger than all keys in the tree, 
// returns NULL.
Vertex* find(Vertex*& root, int key) {
	Vertex* v = root;
	Vertex* last = root;
	Vertex* next = NULL;
	while (v != NULL) {
		if (v->key >= key && (next == NULL || v->key < next->key)) {
			next = v;
		}
		last = v;
		if (v->key == key) {
			break;      
		}
		if (v->key < key) {
			v = v->right;
		} else {
			v = v->left;
		}
	}
	splay(root, last);
	return next;
}

void split(Vertex* root, int key, Vertex*& left, Vertex*& right) {
	right = find(root, key);
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

// Code that uses splay tree to solve the problem

Vertex* root = NULL;
bool debug = false;

void insert(int x) {
	Vertex* left = NULL;
	Vertex* right = NULL;
	Vertex* new_vertex = find(root, x);
	if (new_vertex == NULL || new_vertex->key != x) {
		split(root, x, left, right);
		new_vertex = new Vertex(x, x, NULL, NULL, NULL);
		root = merge(left, merge(new_vertex, right));
	}
	if (debug) printTree(root, 0);
}

void erase(int x) {
	Vertex* found = find(root, x);              
	if (found != NULL && found->key == x) {
		Vertex* left = NULL;
		Vertex* temp_left = NULL;
		Vertex* right = NULL;
		Vertex* temp_right = NULL;
		split(root, x, left, temp_right);
		split(temp_right, x + 1, temp_left, right);
		if (right != NULL) {
			if (left != NULL) {
				root = merge(left, right);
			} else {
				root = right;
			}
		} else {
			root = left;
		}
	}
	if (debug) printTree(root, 0);
	return;
}

bool find(int x) {
	Vertex* found = find(root, x);
	if (found != NULL && found->key == x) {
		return true;
	}
	return false;
}

long long sum(int from, int to) {
	Vertex* left = NULL;
	Vertex* middle = NULL;
	Vertex* temp_middle = NULL;
	Vertex* right = NULL;
	split(root, from, left, temp_middle);
	split(temp_middle, to + 1, middle, right);
	long long ans = 0;
	if (middle != NULL) {
	    ans = middle->sum;
	}
	root = merge(merge(left, middle), right);
	return ans;  
}

const int MODULO = 1000000001;

int rec[1000006];
void printTree(struct Vertex* curr, int depth) {
	int i;
	if (curr == NULL) return;
	cout << "\t";
	string tmp_str;
	for(i = 0; i < depth; i++) {
		if(i == depth - 1) {
			tmp_str = rec[depth-1] ? "+" : "L";
			cout << tmp_str << "---";
		} else {
			tmp_str = rec[i] ? "|" : "  ";
			cout << tmp_str << "   ";
		}
	}
	cout << curr->key << "\n";
	rec[depth] = 1;
	printTree(curr->left, depth + 1);
	rec[depth] = 0;
	printTree(curr->right, depth + 1);
}

int main() {
	int n;
	cin >> n;
	int last_sum_result = 0;
	for (int i = 0; i < n; i++) {
		char type;
		cin >> type;
		switch (type) {
			case '+' : {
				int x;
				cin >> x;
				insert((x + last_sum_result) % MODULO);
				if (debug) cout << "   Added " << ((x + last_sum_result) % MODULO) << std::endl;
			} break;
			case '-' : {
				int x;
				cin >> x;
				erase((x + last_sum_result) % MODULO);
				if (debug) cout << "   Erased " << ((x + last_sum_result) % MODULO) << std::endl;
			} break;            
			case '?' : {
				int x;
				cin >> x;
				string find_result;
				find_result = find((x + last_sum_result) % MODULO) ? "Found" : "Not found";
				cout << find_result << std::endl;
			} break;
			case 's' : {
				int l, r;
				cin >> l >> r;
				long long res = sum((l + last_sum_result) % MODULO, (r + last_sum_result) % MODULO);
				cout << res << std::endl;
				last_sum_result = int(res % MODULO);
			}
		}
		// if (i == 64) {
		// 	cout << "  After 64:  \n";
		// 	printTree(root, 0);
		// }
		// if (i == 65) {
		// 	cout << "  After 65:  \n";
		// 	printTree(root, 0);
		// }
	}
	return 0;
}
