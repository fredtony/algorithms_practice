#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>

using namespace std;

struct point {
    double x, y;
};

double dist(point p0, point p1) {
    return sqrt(pow((p0.x - p1.x), 2.) + pow((p0.y - p1.y), 2.));
}

double minimal_distance(vector<point> &points, int l, int r) {
    int gap = r-l;
    if (gap < 2) return HUGE_VALF;
    if (gap == 2)  {
        double d = dist(points[l], points[l+1]);
        return d;
    }
    int mid = l + gap / 2;
    double d = fmin(minimal_distance(points, l, mid), minimal_distance(points, mid, r));
    point left_point; left_point.x = points[mid].x - d;
    int left_elem = (int)(lower_bound(points.begin()+l, points.begin()+r, left_point,
                                      [](point const &a, point const &b) -> bool {return a.x < b.x;})-points.begin());
    point right_point; right_point.x = points[mid].x + d;
    int right_elem = (int)(upper_bound(points.begin()+l, points.begin()+r, right_point,
                                       [](point const &a, point const &b) -> bool {return a.x < b.x;})-points.begin());

    if (left_elem >= right_elem-1) {
        return d;
    }
    vector<point> y_sorted(right_elem-left_elem);
    if (left_elem >= right_elem) {
        return d;
    }
    for (int i=left_elem; i<right_elem; i++) {
        int j = i - left_elem;
        point pt; pt.x = points[i].x; pt.y = points[i].y;
        y_sorted[j] = pt;
    }
    sort(y_sorted.begin(), y_sorted.end(), [](point const &a, point const &b) -> bool {return a.y < b.y;});
    for (int i=0; i<(int)y_sorted.size()-1; ++i){
        int end = min((int)y_sorted.size(), i+8);
        for (int j=i+1; j<end; ++j) {
            double new_d = dist(y_sorted[i], y_sorted[j]);
            d = fmin(d, new_d);
        }
    }
    return d;
}

int main() {
    size_t n;
    cin >> n;
    vector<point> points(n);
    for (size_t i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }
    sort(points.begin(), points.end(), [](point const &a, point const &b) -> bool {return a.x < b.x;});
    cout << fixed;
    cout << setprecision(9) << minimal_distance(points, 0, points.size()) << '\n';
}
