#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <cassert>

using std::cin;
using std::cout;
using std::endl;
using std::make_pair;
using std::pair;
using std::string;
using std::vector;
using std::sort;

bool const debug = false;
// int const Letters = 5;

// int idx(char letter) {
// 	switch (letter) {
// 		case '$': return 0; break;
// 		case 'A': return 1; break;
// 		case 'C': return 2; break;
// 		case 'G': return 3; break;
// 		case 'T': return 4; break;
// 		default: assert(false); return -1;
// 	}
// }

// vector<vector<int>> createFMIndex(const string& bwt) {
// 	vector<vector<int>> result;
// 	vector<int> row (Letters, 0);

// 	result.push_back(row);
// 	for (int i = 0; i < bwt.size(); ++i) {
// 		++row[idx(bwt[i])];
// 		result.push_back(row);
// 	}
// 	int count = 0;
// 	for (int i = 0; i < Letters; ++i) {
// 		row[i] = count;
// 		count += result[bwt.size()][i];
// 	}
// 	result.push_back(row);
// 	return result;
// }

// string InverseBWT(const string& bwt) {
// 	char nextChar = bwt[0];
// 	string text = bwt;
// 	text[text.size()-1] = '$';
// 	text[text.size()-2] = nextChar;
// 	vector<vector<int>> fmIndex = createFMIndex(bwt);

// 	vector<int> tracker = fmIndex[fmIndex.size()-1];
// 	int c = idx(nextChar);
// 	int pred = tracker[c] + fmIndex[0][c];
// 	int count = text.size() - 3;
// 	while (pred != 0) {
// 		nextChar = bwt[pred];
// 		c = idx(nextChar);
// 		pred = tracker[c] + fmIndex[pred][c];
// 		if (count >= 0) {
// 			text[count--] = nextChar;
// 		}
// 	}

// 	return text;
// }

// Build suffix array of the string text and
// return a vector result of the same length as the text
// such that the value result[i] is the index (0-based)
// in text where the i-th lexicographically smallest
// suffix of text starts.
vector<int> BuildSuffixArray(const string& text) {
	vector<int> result;
	vector<string> suffix;
	// string realText = InverseBWT(text);
	// if (debug) cout << realText << endl;
	// for (int i = 0; i < text.size(); ++i) {
	// 	suffix.push_back(realText.substr(i, text.size() - i));
	// }
	// sort(suffix.begin(), suffix.end());
	for (int i = 0; i < text.size(); ++i) {
		suffix.push_back(text.substr(i, text.size() - i));
	}
	sort(suffix.begin(), suffix.end());
	for (int i = 0; i < suffix.size(); ++i) {
		if (debug) cout << suffix[i] << endl;
		result.push_back(text.size() - suffix[i].size());
	} if (debug) cout << endl << endl;

	return result;
}

int main() {
	string text;
	cin >> text;
	vector<int> suffix_array = BuildSuffixArray(text);
	for (int i = 0; i < suffix_array.size(); ++i) {
		cout << suffix_array[i] << ' ';
	}
	cout << endl;
	return 0;
}
