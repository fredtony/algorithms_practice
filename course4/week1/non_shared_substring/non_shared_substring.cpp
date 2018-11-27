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
using std::get;
using std::make_tuple;

int const Letters = 6;
int const NA = -1;
bool debug = false;
string nullChar = " ";

int letterToIndex (char letter) {
	switch (letter) {
		case 'A': return 0; break;
		case 'C': return 1; break;
		case 'G': return 2; break;
		case 'T': return 3; break;
		case '$': return 4; break;
		case '#': return 5; break;
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

	int findLength(const string& text) {
		if (end == -1) {
			return text.size() - start;
		} else {
			return end - start + 1;
		}
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

	tuple<bool, string> shortestSubstring(const string& text, vector<Node>& tree) {
		bool firstOnly = true;
		string minSubstring = nullChar, nextSubstring;
		std::size_t first;
		for (int i = 0; i < Letters - 2; ++i) {
			//// NEED TO FIX EDGE CASE WHEN $ is by itself on a branch, it needs to change firstOnly to false
			if (edges[i].start == -1) {
				continue;
			}
			first = text.find("#", edges[i].start);
			if (first == string::npos) {
				// This options means that anything on or past this edge is from second string
				firstOnly = false;
			} else if (edges[i].end == -1 || first <= edges[i].end) {
				// Leaf nodes that contain part of the first string
				// or branches that include the first stop character
				nextSubstring = text[edges[i].start];
				if (minSubstring == nullChar || nextSubstring.size() < minSubstring.size()) {
					minSubstring = nextSubstring;
				}
			} else {
				// Branch nodes that need to be further explored
				tuple<bool, string> branchResult = tree[edges[i].nextNode].shortestSubstring(text, tree);
				firstOnly = (firstOnly && get<0>(branchResult));
				if (get<1>(branchResult) != nullChar) {
					nextSubstring = text.substr(edges[i].start, edges[i].findLength(text)) + get<1>(branchResult);
					if (minSubstring == nullChar || nextSubstring.size() < minSubstring.size()) {
						minSubstring = nextSubstring;
					}
				}
			}
		}
		if (edges[letterToIndex('$')].start != -1) {
			firstOnly = false;
		}
		// for (int i = 0; i < Letters - 2; ++i) {
		// 	if (edges[i].start == -1) {
		// 		continue;
		// 	}
		// 	cout << text.substr(edges[i].start, edges[i].findLength(text)) << endl;
		// }
		// cout << "\tfirstOnly=" << firstOnly << " , minSubstring=" << minSubstring << endl;
		if (firstOnly) {
			return make_tuple(firstOnly, "");
		} else {
			return make_tuple(firstOnly, minSubstring);
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

// string searchTree(const string& p, vector<Node>& tree, int currNode, string result) {
// 	int minTreeSize, minBranch, currLength;
// 	string minSubstring;
// 	for (int i = 0; i < Letters - 2; ++i) {
// 		if (!tree[currNode].edges[i].hasSubstring(text, tree)) {
// 			currLength = tree[currNode].edges[i].end - tree[currNode].edges[i].start + 1;
// 			if (currLength < minTreeSize) {
// 				minTreeSize = currLength;
// 				minSubstring = text.substr(tree[currNode].edges[i].start, currLength);
// 			}
// 			return result + text.substr(tree[edges[i]]);
// 		}
// 	}
// 	return result;
// }

int main(void) {
	string result = "", p, q;
	cin >> p;
	cin >> q;
	string text = p + "#" + q + "$";

	vector<Node> tree = build_tree(text);

	tuple<bool, string> ans = tree[0].shortestSubstring(text, tree);

	cout << get<1>(ans) << endl;

	return 0;
}
