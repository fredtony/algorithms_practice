#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;
using std::cin;
using std::cout;
using std::find;

struct Query {
	string type, s;
	size_t ind;
};

struct Node {
    string name;
    Node * next_node;
    Node(string name) : name(name), next_node(nullptr) {}
};

class QueryProcessor {
	int bucket_count;
	vector<Node *> elems;
	size_t hash_func(const string& s) const {
		static const size_t multiplier = 263;
		static const size_t prime = 1000000007;
		unsigned long long hash = 0;
		for (int i = static_cast<int> (s.size()) - 1; i >= 0; --i)
			hash = (hash * multiplier + s[i]) % prime;
		return hash % bucket_count;
	}

public:
	explicit QueryProcessor(int bucket_count): bucket_count(bucket_count) {
		elems.resize(bucket_count, nullptr);
	}

	Query readQuery() const {
		Query query;
		cin >> query.type;
		if (query.type != "check")
			cin >> query.s;
		else
			cin >> query.ind;
		return query;
	}

	void writeSearchResult(bool was_found) const {
		cout << (was_found ? "yes\n" : "no\n");
	}

	void processQuery(const Query& query) {
		Node * node;
		if (query.type == "check") {
			// cout << "check\n";
			string out;
			node = elems[query.ind];
			if (node == nullptr)
				out = ' ';
			else {
				out = node->name;
				node = node->next_node;
				while (node != nullptr) {
					out = node->name + " " + out;
					node = node->next_node;
				}
			}
			cout << out << "\n";
		} else {
			unsigned int hash_val = hash_func(query.s);
			node = elems[hash_val];
			if (query.type == "find") {
				bool was_found = false;
				// cout << "find\n";
				while (node != nullptr) {
					if (node->name == query.s) {
						was_found = true;
						break;
					}
					node = node->next_node;
				}
				writeSearchResult(was_found);
			}
			else if (query.type == "add") {
				// cout << "add\n";
				if (node == nullptr)
					elems[hash_val] = new Node(query.s);
				else {
					while (true) {
						if (node->name == query.s) {
							break;
						}
						if (node->next_node == nullptr) {
							node->next_node = new Node(query.s);
							break;
						}
						node = node->next_node;
					}
				}
			} else if (query.type == "del") {
				// cout << "delete\n";
				if (node == nullptr) {}
				else if (node->name == query.s) {
					elems[hash_val] = node->next_node;
					delete node;
				}
				else {
					while (node->next_node != nullptr) {
						if (node->next_node->name == query.s) {
							Node * tmp_node = node->next_node;
							node->next_node = node->next_node->next_node;
							delete tmp_node;
							break;
						}
						node = node->next_node;
					}
				}
			}
		}
	}

	void processQueries() {
		int n;
		cin >> n;
		for (int i = 0; i < n; ++i)
			processQuery(readQuery());
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	int bucket_count;
	cin >> bucket_count;
	QueryProcessor proc(bucket_count);
	proc.processQueries();
	return 0;
}
