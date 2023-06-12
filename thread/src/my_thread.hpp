#include <thread>

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