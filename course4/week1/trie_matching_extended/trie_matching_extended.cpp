#include <algorithm>
#include <cassert>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int const Letters = 4;
int const NA = -1;
bool debug = false;

struct Node {
	int next [Letters];
	bool patternEnd;

	Node() {
		fill(next, next + Letters, NA);
		patternEnd = false;
	}
};

int letterToIndex (char letter) {
	switch (letter) {
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		default: assert(false); return -1;
	}
}

vector<Node> build_trie(const vector<string>& patterns) {
	vector<Node> trie;
	Node root;
	trie.push_back(root);
	int curr_char, curr_node = 0;
	for (int i = 0; i < patterns.size(); ++i) {
		curr_node = 0;
		for (int j = 0; j < patterns[i].size(); ++j) {
			curr_char = letterToIndex(patterns[i][j]);
			if (trie[curr_node].next[curr_char] == -1) {
				trie[curr_node].next[curr_char] = trie.size();
				curr_node = trie.size();
				Node new_node;
				trie.push_back(new_node);
			} else {
				curr_node = trie[curr_node].next[curr_char];
				if (trie[curr_node].patternEnd) {
					break;
				}
			}
		}
		trie[curr_node].patternEnd = true;
	}
	return trie;
}

bool check_trie(const string& text, int idx, const vector<Node>& trie) {
	if (debug) cout << "Trying node " << idx << endl;
	int i = idx;
	int curr_node = 0, next_node;
	while (i < text.size()) {
		if (debug) cout << "\tChecking letter " << text[i] << endl;
		int curr_char = letterToIndex(text[i++]);
		next_node = trie[curr_node].next[curr_char];
		if (next_node != -1) {
			if (trie[next_node].patternEnd) {
				return true;
			}
			curr_node = next_node;
		} else {
			return false;
		}
	}
	return false;
}

vector<int> solve (const string& text, int n, const vector<string>& patterns) {
	vector<int> result;
	vector<Node> trie = build_trie(patterns);

	if (debug) {
		for (int i = 0; i < trie.size(); ++i) {
			for (int j = 0; j < 4; ++j) {
				if (trie[i].next[j] != -1) {
					cout << i << "/" << j << "->" << trie[i].next[j] << endl;
				}
			}
		}
	}

	for (int i = 0; i < text.size(); ++i) {
		if (check_trie(text, i, trie)) {
			result.push_back(i);
		}
	}

	return result;
}

int main (void)
{
	string text;
	cin >> text;

	int n;
	cin >> n;

	vector <string> patterns (n);
	for (int i = 0; i < n; i++) {
		cin >> patterns[i];
	}

	vector<int> ans;
	ans = solve(text, n, patterns);

	for (int i = 0; i < (int) ans.size (); i++) {
		cout << ans[i];
		if (i + 1 < (int) ans.size ()) {
			cout << " ";
		}
		else {
			cout << endl;
		}
	}

	return 0;
}
