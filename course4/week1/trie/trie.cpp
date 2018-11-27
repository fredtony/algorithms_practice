#include <string>
#include <iostream>
#include <vector>
#include <map>

using std::map;
using std::vector;
using std::string;

typedef map<char, int> edges;
typedef vector<edges> trie;

trie build_trie(vector<string> & patterns) {
	trie t;
	edges root;
	t.push_back(root);
	int curr_trie;
	char curr_char;
	edges::const_iterator it;
	for (int i = 0; i < patterns.size(); ++i) {
		curr_trie = 0;
		for (int j = 0; j < patterns[i].size(); ++j) {
			curr_char = patterns[i][j];
			it = t[curr_trie].find(curr_char);
			if (it == t[curr_trie].end()) {
				t[curr_trie][curr_char] = t.size();
				edges new_node;
				t.push_back(new_node);
				curr_trie = t[curr_trie][curr_char];
			} else {
				curr_trie = it->second;
			}
		}
	}
	return t;
}

int main() {
	size_t n;
	std::cin >> n;
	vector<string> patterns;
	for (size_t i = 0; i < n; i++) {
		string s;
		std::cin >> s;
		patterns.push_back(s);
	}

	trie t = build_trie(patterns);
	for (size_t i = 0; i < t.size(); ++i) {
		for (const auto & j : t[i]) {
			std::cout << i << "->" << j.second << ":" << j.first << "\n";
		}
	}

	return 0;
}