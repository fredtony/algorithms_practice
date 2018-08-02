#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::cin;
using std::cout;
using std::swap;
using std::pair;
using std::make_pair;

class HeapBuilder {
private:
	vector<int> data_;
	vector< pair<int, int> > swaps_;

	void WriteResponse() const {
		cout << swaps_.size() << "\n";
		for (int i = 0; i < swaps_.size(); ++i) {
			cout << swaps_[i].first << " " << swaps_[i].second << "\n";
		}
	}

	void ReadData() {
		int n;
		cin >> n;
		data_.resize(n);
		for(int i = 0; i < n; ++i)
			cin >> data_[i];
	}
    
    void SiftDown(int parent) {
        int min_idx, left_child = parent * 2 + 1;
        if (left_child >= data_.size())
            return;
        else {
    		int right_child = left_child + 1;
    		if (right_child == data_.size())
    		    min_idx = left_child;
    		else
    		    min_idx = (data_[left_child] < data_[right_child] ? left_child : right_child);
    		if (data_[min_idx] < data_[parent]) {
    			swaps_.push_back(pair<int,int>(parent, min_idx));
    			swap(data_[min_idx], data_[parent]);
    			SiftDown(min_idx);
    		}
        }
    }
    
	void GenerateSwaps() {
		swaps_.clear();
		for (int i = (data_.size() / 2) - 1; i >= 0; --i) {
			SiftDown(i);
		}
	}

public:
	void Solve() {
		ReadData();
		GenerateSwaps();
		WriteResponse();
	}
};

int main() {
	std::ios_base::sync_with_stdio(false);
	HeapBuilder heap_builder;
	heap_builder.Solve();
	return 0;
}
