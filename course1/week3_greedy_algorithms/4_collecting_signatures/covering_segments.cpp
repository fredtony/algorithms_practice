#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Segment {
    unsigned int start, end;
    bool operator<(const Segment& seg2) const {
        if (end != seg2.end) return end > seg2.end;
        else return start > seg2.start;
    }
};

vector<unsigned int> optimal_points(vector<Segment> segments) {
    vector<unsigned int> points;
    unsigned int j = 0;
    sort(segments.begin(), segments.end());
    // for (unsigned int i = 0; i < segments.size(); ++i) {
    //     cout << segments[i].start << '/' << segments[i].end << ' ';
    // }
    // cout << endl << endl;
    while (!segments.empty()) {
        points.push_back(segments.back().end);
        segments.pop_back();
        while (!segments.empty() and points.back() >= segments.back().start) {
            segments.pop_back();
        }
    }
    return points;
}

int main() {
    int n;
    cin >> n;
    vector<Segment> segments(n);
    for (size_t i = 0; i < segments.size(); ++i) {
        cin >> segments[i].start >> segments[i].end;
    }
    vector<unsigned int> points = optimal_points(segments);
    cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        cout << points[i] << " ";
    }
}
