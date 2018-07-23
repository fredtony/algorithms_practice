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
    int x, y;
};

float dist(point p0, point p1) {
    return sqrt(pow((float)(p0.x - p1.x), 2.) + pow((float)(p0.y - p1.y), 2.));
}

double minimal_distance(vector<point> &points, int l, int r) {
    cout << l << '/' << r << endl;
    int gap = r-l;
    if (gap < 2) return HUGE_VALF;
    if (gap == 2)  {
        float d = dist(points[l], points[l+1]);
        cout << ' ' << d << endl;
        return d;
    }
    int mid = (int)points.size() / 2;
    float d = fmin(minimal_distance(points, l, mid), minimal_distance(points, mid, r));
    vector<point> y_sorted(gap);
    for (int i=l; i<r; i++) {
        y_sorted.push_back(points[i]);
    }
    sort(y_sorted.begin(), y_sorted.end(), [](point const &a, point const &b) -> bool {return a.y < b.y;});
    for (int i=l; i<r-1; ++i){
        int end = min(r, i+8);
        for (int j=i+1; j<end; ++i) {
            d = fmin(d, dist(y_sorted[i], y_sorted[j]));
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
