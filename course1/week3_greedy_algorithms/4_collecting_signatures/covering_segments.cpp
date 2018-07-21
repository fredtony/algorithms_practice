#include <algorithm>
#include <iostream>
#include <climits>
#include <vector>
#include <list>

using namespace std;

struct Segment {
    int start, end;
};

vector<int> optimal_points(vector<Segment> &segments) {
    vector<int> points;
    while ( segments.size() > 0 ) {
        Segment seg = segments[segments.size()-1];
        segments.pop_back();
        if ( segments.size() > 0 ) {
            int max_point = seg.start, max_intervals = 0, num_intervals = 0;
            list<unsigned int> max_seg_list;
            for ( int j=seg.start; j<=seg.end; ++j ) {
                num_intervals = 0;
                list<unsigned int> seg_list;
                for ( unsigned int k=0; k<segments.size(); ++k ) {
                    if ( j >= segments[k].start and j <= segments[k].end ) {
                        num_intervals++;
                        seg_list.push_back(k);
                    }
                }
                if ( num_intervals > max_intervals ) {
                    max_point = j;
                    max_intervals = num_intervals;
                    max_seg_list = seg_list;
                }
            }
            points.push_back(max_point);
            while (!max_seg_list.empty()) {
                if (max_seg_list.front() != segments.size()-1) {
                    segments[max_seg_list.front()] = segments[segments.size()-1];
                }
                segments.pop_back();
                max_seg_list.pop_front();
            }
        }
        else {
            points.push_back(seg.start);
            break;
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
    vector<int> points = optimal_points(segments);
    cout << points.size() << "\n";
    for (size_t i = 0; i < points.size(); ++i) {
        cout << points[i] << " ";
    }
}
