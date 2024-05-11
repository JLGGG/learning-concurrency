#include <thread>
#include <chrono>
#include <cmath>
#include <numeric>
#include <vector>
#include <iostream>
#include <memory>
#include <fmt/core.h>

using namespace std;

class ThreadGuard {
private: 
    thread &thr;
public:
    explicit ThreadGuard(thread &t) : thr(t) {}
    ~ThreadGuard() {
        static int i = 1;
        if(thr.joinable()) thr.join();
        fmt::print("ThreadGuard destructor: {}\n", i++);
    }

    ThreadGuard & operator=(const ThreadGuard &o) = delete;
    ThreadGuard(const ThreadGuard &o) = delete;
};

struct PartialSumFunctor {
    vector<double>::iterator start;
    vector<double>::iterator end;
    double res = 0;

    void operator() ();
};

void PartialSumFunctor::operator() () {
    for (auto i = start; i < end; i++) {
        res += *i;
    }
}

int main(int argc, char **argv) {
    const int num_thr = thread::hardware_concurrency();
    int N = atoi(argv[1]);
    int step = (int)std::ceil(N*1.0/num_thr);
    // double res[num_thr];

    vector<double> data(N);
    std::iota(data.begin(), data.end(), 1);
    // thread *thr[num_thr];
    unique_ptr<thread> thr[num_thr];
    unique_ptr<ThreadGuard> tg[num_thr];
    PartialSumFunctor f[num_thr];
    vector<double>::iterator local_start = data.begin();
    vector<double>::iterator local_end;
    for (int i = 0; i < num_thr; i++) {
        local_end = local_start + step;
        if (i==num_thr-1) local_end = data.end();
        f[i].start = local_start;
        f[i].end = local_end;
        thr[i] = make_unique<thread>(ref(f[i]));
        tg[i] = make_unique<ThreadGuard>(ref(*thr[i]));
        local_start += step;
    }

    this_thread::sleep_for(std::chrono::seconds(1)); // this code waits when all threads are terminated.
    double total = 0;
    for (int i = 0; i < num_thr; i++) {
        // thr[i]->join();
        total += f[i].res;
    }

    // cout << "Average is: " << total/N << endl;
    fmt::print("Average is: {}\n", total/N);
}