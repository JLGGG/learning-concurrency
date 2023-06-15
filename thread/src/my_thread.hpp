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

class JoiningThread {
private:
    std::thread t_;
public:
    JoiningThread() noexcept = default;

    template<typename Callable, typename ... Args>
    explicit JoiningThread(Callable&& func, Args&& ... args) : 
    t_(std::forward<Callable>(func), std::forward<Args>(args)...) {}
    
    explicit JoiningThread(std::thread t) noexcept: t_{std::move(t)} {}

    JoiningThread(JoiningThread&& other) noexcept: t_{std::move(other.t_)} {}

    JoiningThread(const JoiningThread&) = delete;
    JoiningThread& operator=(JoiningThread&) = delete;

    JoiningThread& operator=(JoiningThread&& other) noexcept {
        if(joinable()) join();
        t_ = std::move(other.t_);
        return *this;
    }

    JoiningThread& operator=(std::thread other) noexcept {
        if(joinable()) join();
        t_ = std::move(other);
        return *this;
    }

    ~JoiningThread() noexcept {
        if (joinable()) join();
    }

    void swap(JoiningThread& other) noexcept {
        t_.swap(other.t_);
    }

    std::thread::id getId() const noexcept {
        return t_.get_id();
    }

    bool joinable() const noexcept {
        return t_.joinable();
    }

    void join() {
        t_.join();
    }

    void detach() {
        t_.detach();
    }
    std::thread& asThread() noexcept {
        return t_;
    }

    const std::thread& asThread() const noexcept {
        return t_;
    }
};
struct func {
    int& i_;
    int sum = 0;
    func(int& i) : i_{i} {}
    void operator()() {
        for (unsigned j=i_; j<=1000; ++j) {
            sum += j;
        }
        fmt::print("sum result: {}\n", sum);
    }
};

void myPrint(std::string const& str) {
    fmt::print("{}\n", str);
}

void numPrint(int n) {
    fmt::print("{}\n", n);
}