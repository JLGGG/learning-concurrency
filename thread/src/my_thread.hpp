#include <thread>
#include <fmt/core.h>

class ThreadGuard {
private:
    std::thread& t_;
public:
    explicit ThreadGuard(std::thread& t) : t_{t} {}
    ~ThreadGuard() {
        if (t_.joinable()) {
            t_.join();
        }
    }
    ThreadGuard(ThreadGuard const&) = delete;
    ThreadGuard& operator=(ThreadGuard const&) = delete;
};

struct func {
    int& i_;
    int sum = 0;
    func(int& i) : i_{i} {}
    void operator()() {
        for (unsigned j=i_; j<=1000000; ++j) {
            sum += j;
        }
        fmt::print("sum result: {}\n", sum);
    }
};

void myPrint(std::string const& str) {
    fmt::print("{}\n", str);
}