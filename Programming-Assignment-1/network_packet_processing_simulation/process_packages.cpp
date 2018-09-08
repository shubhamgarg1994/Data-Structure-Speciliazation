#include <iostream>
#include <queue>
#include <vector>

struct Request {
    Request(int arrival_time, int process_time):
        arrival_time(arrival_time),
        process_time(process_time)
    {}

    int arrival_time;
    int process_time;
};

struct Response {
    Response(bool dropped, int start_time):
        dropped(dropped),
        start_time(start_time)
    {}

    bool dropped;
    int start_time;
};

class Buffer {
public:
    Buffer(int size):
        size_(size),
        finish_time_(),
        buffer_availability(size)
    {}

    Response Process(const Request &request) {
        // write your code here
        struct Response response(0,request.arrival_time);
        int finish_time_back = 0;

        if(this->size_ >= 0)
        {
            response.dropped = 0;
            if(!this->finish_time_.empty())
            {
              finish_time_back = this->finish_time_.back();

              response.start_time = (request.arrival_time > finish_time_back ? request.arrival_time : finish_time_back);

                if((this->finish_time_.front() > request.arrival_time))
                {
                    if(this->size_ != 0)
                    {
                        this->size_ --;
                        this->finish_time_.push(response.start_time + request.process_time);
                    }
                    else
                    {
                        response.dropped = -1;
                    }
                }
                else
                {
                    this->finish_time_.pop();
                    this->finish_time_.push(response.start_time + request.process_time);
                    //this->size_ ++;
                }
            }
            else
            {
                response.start_time = request.arrival_time;
                this->finish_time_.push(response.start_time + request.process_time);
                this->size_ --; 
            }
        }
        else
        {
            response.dropped = 1;
        }
    return response;
}
private:
    int size_;
    int buffer_availability;
    std::queue <int> finish_time_;
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
