#include <gtest/gtest.h>
#include <functional>

#include "my_thread.hpp"

class TestThread : public ::testing::Test {
protected:
    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }
};

TEST_F(TestThread, test1) {
    int local_state=0;
    func my_func(local_state);
    std::thread my_thread(my_func);
    // my_thread.detach();
    // my_thread.join();
    ThreadGuard t1(my_thread);
    std::thread passing_thread(myPrint, "Hello world");
    ThreadGuard t2(passing_thread);

    std::vector<JoiningThread> threads;
    for (int i=0; i<5; i++) {
        threads.emplace_back(numPrint, i);
    }

    // for(auto& item : threads) {
    //     item.join();
    // }
}