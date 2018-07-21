#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

double get_optimal_value(int capacity, vector<int> weights, vector<int> values) {
    double value = 0.0;
    int num_items = weights.size();
    vector<double> densities(num_items);
    unsigned int i;
    for ( int i=0; i<num_items; ++i ) {
        densities[i] = (double) values[i] / (double) weights[i];
    }
    while ( capacity > 0 and densities.size() > 0) {
        i = distance(densities.begin(), max_element(densities.begin(), densities.end()));
        if (capacity <= weights[i]) {
            value += densities[i] * (double) capacity;
            capacity = 0;
            break;
        }
        else {
            value += (double) values[i];
            capacity -= weights[i];
            if (i != weights.size()-1) {
                weights[i] = weights[weights.size()-1];
                values[i] = values[values.size()-1]; 
                densities[i] = densities[densities.size()-1];
            }
            weights.pop_back(); values.pop_back(); densities.pop_back();
        }
    }
    return value;
}

int main() {
    int n, capacity;
    cin >> n >> capacity;
    vector<int> values(n);
    vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        cin >> values[i] >> weights[i];
    }

    double optimal_value = get_optimal_value(capacity, weights, values);

    cout.precision(10);
    cout << optimal_value << endl;
    return 0;
}
