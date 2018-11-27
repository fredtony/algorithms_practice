#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <tuple>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;
using std::tuple;

int const Letters = 5;
int const NA = -1;
bool debug = false;

int letterToIndex (char letter) {
	switch (letter) {
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		case '$': return 4; break;
		default: assert(false); return -1;
	}
}

class Edge {
public:
	int start, end, nextNode;

	Edge() {
		start = -1; end = -1; nextNode = -1;
	};
	Edge(int startLoc) {
		start = startLoc; end = -1; nextNode = -1;
	};
	Edge(int startLoc, int endLoc) {
		start = startLoc; end = endLoc; nextNode = 1;
	};
	Edge(int startLoc, int endLoc, int nextNodeIdx) {
		start = start; end = end; nextNode = nextNodeIdx;
	};
};

class Node {
public:
	int suffixLink;
	// edges element is start position, end position, node it points to
	vector<Edge> edges;

	Node(int currChar, int start) {
		for (int i = 0; i < Letters; ++i) {
			if (i == currChar) {
				edges.push_back(Edge(start));
			} else {
				edges.push_back(Edge());
			}
		}
		suffixLink = 0;
	};

	Node() {
		for (int i = 0; i < Letters; ++i) {
			edges.push_back(Edge());
		}
		suffixLink = 0;
	};

	void printNode(int idx) {
		cout << "Node" << idx << ":" << endl;
		for (int i = 0; i < Letters; ++i) {
			cout << "\tEdge " << i << ": start=" << edges[i].start << ", end=" << edges[i].end;
			cout << ", nextNode=" << edges[i].nextNode << endl;
		}
	};
};

class activePoint {
public:
	int activeNode, activeEdge, activeEdgeChar, activeLength;

	activePoint() {
		activeNode = 0; activeEdge = -1; activeLength = 0; activeEdgeChar = -1;
	};

	void updateActiveEdge(const string& text, int i) {
		activeEdge = i;
		activeEdgeChar = letterToIndex(text[i]);
		return;
	};

	bool walkDown(vector<Node>& tree, const string& text) {
		int length;
		if (tree[activeNode].edges[activeEdgeChar].end == NA) {
			return false;
		} else {
			length = tree[activeNode].edges[activeEdgeChar].end - tree[activeNode].edges[activeEdgeChar].start + 1;
			if (activeLength < length) {
				return false;
			} else {
				activeNode = tree[activeNode].edges[activeEdgeChar].nextNode;
				updateActiveEdge(text, activeEdge + length);
				activeLength -= length;
				return true;
			}
		}
	};

	void print() {
		cout << "activeNode=" << activeNode << ", activeEdge=" << activeEdge;
		cout << ", activeEdgeChar=" << activeEdgeChar << ", activeLength=" << activeLength << endl;
	}
};

vector<Node> build_tree(const string& text) {
	vector<Node> tree;
	Node root = Node();
	tree.push_back(root);

	int currChar, nextChar, newNodeIndex, lastNewNode = NA, remainingSuffixCount = 0;
	activePoint ap = activePoint();
	for (int i = 0; i < text.size(); ++i) {
		remainingSuffixCount++;
		lastNewNode = NA;
		currChar = letterToIndex(text[i]);
		// cout << "\nIteration " << i << ", currChar is " << currChar << endl;
		// ap.print();
		while (remainingSuffixCount > 0) {
			if (ap.activeLength == 0) {
				ap.updateActiveEdge(text, i);
			}
			// cout << "Tree has " << tree.size() << " nodes.\n";
			// for (int i = 0; i < tree.size(); ++i) {
			// 	tree[i].printNode(i);
			// }
			// cout << "remainingSuffixCount is " << remainingSuffixCount << endl;
			// cout << "lastNewNode is " << lastNewNode << endl;
			// ap.print();
			if (tree[ap.activeNode].edges[ap.activeEdgeChar].start == NA) { // case 2 - no existing edge
				tree[ap.activeNode].edges[ap.activeEdgeChar].start = i;
				// tree[0].printNode(0);
				if (lastNewNode != NA) {
					tree[lastNewNode].suffixLink = ap.activeNode;
					lastNewNode = NA;
				}
			} else {
				if(ap.walkDown(tree, text)) {
					continue;
				}
				nextChar = letterToIndex(text[tree[ap.activeNode].edges[ap.activeEdgeChar].start + ap.activeLength]);
				if (nextChar == currChar) { // case 3
					if (lastNewNode != NA && ap.activeNode > 0) {
						tree[lastNewNode].suffixLink = ap.activeNode;
						lastNewNode = NA;
					}
					ap.activeLength++;
					break;
				}
				// cout << "ADDING NEW NODE!\n";
				Node newNode = Node(currChar, i);
				newNode.edges[nextChar].start = tree[ap.activeNode].edges[ap.activeEdgeChar].start + ap.activeLength;
				newNode.edges[nextChar].end = tree[ap.activeNode].edges[ap.activeEdgeChar].end,
				newNode.edges[nextChar].nextNode = tree[ap.activeNode].edges[ap.activeEdgeChar].nextNode;
				newNodeIndex = tree.size();
				tree.push_back(newNode);
				tree[ap.activeNode].edges[ap.activeEdgeChar].end = tree[ap.activeNode].edges[ap.activeEdgeChar].start + ap.activeLength - 1;
				tree[ap.activeNode].edges[ap.activeEdgeChar].nextNode = newNodeIndex;
				if (lastNewNode != NA) {
					tree[lastNewNode].suffixLink = newNodeIndex;
				}
				lastNewNode = newNodeIndex;
				
			}
			remainingSuffixCount--;
			if (ap.activeNode == 0 && ap.activeLength > 0) {
				ap.activeLength--;
				ap.updateActiveEdge(text, i - remainingSuffixCount + 1); 
			} else if (ap.activeNode != 0) {
				ap.activeNode = tree[ap.activeNode].suffixLink;
			}
		}
	}
	// cout << "Tree has " << tree.size() << " nodes.\n";
	// for (int i = 0; i < tree.size(); ++i) {
	// 	tree[i].printNode(i);
	// }
	return tree;
}

// Build a suffix tree of the string text and return a vector
// with all of the labels of its edges (the corresponding 
// substrings of the text) in any order.
vector<string> ComputeSuffixTreeEdges(const string& text) {
	vector<Node> tree = build_tree(text);
	vector<string> result;
	for (int i = 0; i < tree.size(); ++i) {
		for (int j = 0; j < Letters; ++j) {
			if (tree[i].edges[j].start >= 0) {
				if (tree[i].edges[j].end == -1) {
					result.push_back(text.substr(tree[i].edges[j].start, text.size() - tree[i].edges[j].start));
				} else {
					result.push_back(text.substr(tree[i].edges[j].start, tree[i].edges[j].end - tree[i].edges[j].start + 1));
				}
			}
		}
	}
	// result.push_back("done.");
	return result;
}

int main() {
	string text;
	cin >> text;
	vector<string> edges = ComputeSuffixTreeEdges(text);
	for (int i = 0; i < edges.size(); ++i) {
		cout << edges[i] << endl;
	}
	return 0;
}
