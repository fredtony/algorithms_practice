#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time): arrival_time(arrival_time), process_time(process_time) {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time): dropped(dropped), start_time(start_time) {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size): size_(size), finish_time_() {}

    Response Process(const Request &request) {
        while (!finish_time_.empty() && request.arrival_time >= finish_time_.front()) {
            finish_time_.pop();
        }
        if (finish_time_.empty()) {
            latest_finish = request.arrival_time + request.process_time;
            finish_time_.push(latest_finish);
            // std::cout << "Queue empty. Adding " << latest_finish << " to queue. Start time " << request.arrival_time << std::endl;
            return Response(false, request.arrival_time);
        }
        else if (finish_time_.size() < size_) {
            // std::cout << "Queue non-empty. Adding " << latest_finish + request.process_time << " to end of queue. Start time " << latest_finish << std::endl;
            Response resp = Response(false, latest_finish);
            latest_finish = latest_finish + request.process_time;
            finish_time_.push(latest_finish);
            return resp;
        }
        else {
            // std::cout << "Dropped response." << std::endl;
            return Response(true, 0);
        }
    }
private:
    int size_;
    std::queue <int> finish_time_;
    int latest_finish;
};

std::vector <Request> ReadRequests() {
    std::vector <Request> requests;
    int count;
    std::cin >> count;
    for (int i = 0; i < count; ++i) {
        int arrival_time, process_time;
        std::cin >> arrival_time >> process_time;
        requests.push_back(Request(arrival_time, process_time));
    }
    return requests;
}

std::vector <Response> ProcessRequests(const std::vector <Request> &requests, Buffer *buffer) {
    std::vector <Response> responses;
    for (int i = 0; i < requests.size(); ++i)
        responses.push_back(buffer->Process(requests[i]));
    return responses;
}

void PrintResponses(const std::vector <Response> &responses) {
    for (int i = 0; i < responses.size(); ++i)
        std::cout << (responses[i].dropped ? -1 : responses[i].start_time) << std::endl;
}

int main() {
    int size;
    std::cin >> size;
    std::vector <Request> requests = ReadRequests();

    Buffer buffer(size);
    std::vector <Response> responses = ProcessRequests(requests, &buffer);

    PrintResponses(responses);
    return 0;
}
