#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <tuple>

using std::vector;
using std::cin;
using std::cout;
using std::priority_queue;
using std::greater;

struct queue_elem {
    long long tim;
    int worker;
};

bool operator >(const queue_elem& x, const queue_elem& y) {
    return std::tie(x.tim, x.worker) > std::tie(y.tim, y.worker);
}

class JobQueue {
private:
    int num_workers_;
    vector<int> jobs_;

    vector<int> assigned_workers_;
    vector<long long> start_times_;

    void WriteResponse() const {
        for (int i = 0; i < jobs_.size(); ++i) {
            cout << assigned_workers_[i] << " " << start_times_[i] << "\n";
        }
    }

    void ReadData() {
    int m;
    cin >> num_workers_ >> m;
    jobs_.resize(m);
    for(int i = 0; i < m; ++i)
        cin >> jobs_[i];
    }

    void AssignJobs() {
        assigned_workers_.resize(jobs_.size());
        start_times_.resize(jobs_.size());
        priority_queue<long long, vector<queue_elem>, greater<queue_elem>> next_free_time;
        int min_check = std::min(num_workers_, (int)jobs_.size());
        queue_elem current_elem;
        for (int i = 0; i < min_check; ++i) {
            assigned_workers_[i] = i;
            start_times_[i] = 0;
            next_free_time.push((queue_elem){jobs_[i], i});
        }
        for (int i = num_workers_; i < jobs_.size(); ++i) {
            current_elem = (queue_elem){next_free_time.top().tim, next_free_time.top().worker};
            next_free_time.pop();
            assigned_workers_[i] = current_elem.worker;
            start_times_[i] = current_elem.tim;
            current_elem.tim += (long long)jobs_[i];
            next_free_time.push((queue_elem){current_elem.tim, current_elem.worker});
        }
    }

public:
    void Solve() {
    ReadData();
    AssignJobs();
    WriteResponse();
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    JobQueue job_queue;
    job_queue.Solve();
    return 0;
}
