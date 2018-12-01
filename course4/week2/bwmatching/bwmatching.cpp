#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

const bool debug = false;
const int Letters = 5;
const string alph = "$ACGT";
map<char, int> idx = {{'$', 0}, {'A', 1}, {'C', 2}, {'G', 3}, {'T', 4}};

// Preprocess the Burrows-Wheeler Transform bwt of some text
// and compute as a result:
//   * starts - for each character C in bwt, starts[C] is the first position 
//       of this character in the sorted array of 
//       all characters of the text.
//   * occ_count_before - for each character C in bwt and each position P in bwt,
//       occ_count_before[C][P] is the number of occurrences of character C in bwt
//       from position 0 to position P inclusive.
void PreprocessBWT(const string& bwt, 
                   map<char, int>& starts, 
                   map<char, vector<int> >& occ_count_before) {
	vector<int> newVect (1, 0);
	for (int i = 0; i < Letters; ++i) {
		occ_count_before[alph[i]] = newVect;
	}
	for (int i = 0; i < bwt.size(); ++i) {
		for (char c : alph) {
			if (bwt[i] == c) {
				occ_count_before[c].push_back(occ_count_before[c].back() + 1);
			} else {
				occ_count_before[c].push_back(occ_count_before[c].back());
			}
		}
	}
	int count = 0;
	for (char c: alph) {
		starts[c] = count;
		count += occ_count_before[c].back();
	}
}

// Compute the number of occurrences of string pattern in the text
// given only Burrows-Wheeler Transform bwt of the text and additional
// information we get from the preprocessing stage - starts and occ_counts_before.
int CountOccurrences(const string& pattern, 
                     const string& bwt, 
                     const map<char,int>& starts, 
                     const map<char,vector<int>>& occ_count_before) {
	int top = 0, bottom = bwt.size() - 1;
	string patt = pattern;
	char c;
	while (top <= bottom) {
		if (patt.empty()) {
			return bottom - top + 1;
		} else {
			c = patt.back();
			patt.pop_back();
			if (occ_count_before.at(c)[top] != occ_count_before.at(c)[bottom+1]) {
				top = starts.at(c) + occ_count_before.at(c)[top];
				bottom = starts.at(c) + occ_count_before.at(c)[bottom + 1] - 1;
			} else {
				return 0;
			}
		}
	}
	return -1;
}
     

int main() {
	string bwt;
	cin >> bwt;
	int pattern_count;
	cin >> pattern_count;
	// Start of each character in the sorted list of characters of bwt,
	// see the description in the comment about function PreprocessBWT
	map<char, int> starts;
	// Occurrence counts for each character and each position in bwt,
	// see the description in the comment about function PreprocessBWT
	map<char, vector<int> > occ_count_before;
	// Preprocess the BWT once to get starts and occ_count_before.
	// For each pattern, we will then use these precomputed values and
	// spend only O(|pattern|) to find all occurrences of the pattern
	// in the text instead of O(|pattern| + |text|).
	PreprocessBWT(bwt, starts, occ_count_before);
	if (debug) {
		for (char c: alph) {
			cout << c << ":" << starts[c] << " ";
		} cout << endl << endl;
		for (char c: alph) cout << c << " "; cout << endl;
		for (int i = 0; i < occ_count_before['$'].size(); ++i) {
			for (char c: alph) {
				cout << occ_count_before[c][i] << " ";
			} cout << endl;
		} cout << endl;
	}

	for (int pi = 0; pi < pattern_count; ++pi) {
		string pattern;
		cin >> pattern;
		int occ_count = CountOccurrences(pattern, bwt, starts, occ_count_before);
		if (occ_count == -1) cout << "ERROR";
		cout << occ_count << " ";
	}
	cout << endl;
	return 0;
}
