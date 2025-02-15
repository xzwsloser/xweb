// @Author: loser
// C++20: std::latch,but still remain the C++ standare 17
#pragma once
#include "nocopyable.h"
#include<mutex>
#include<condition_variable>

class CountDownLatch: nocopyable {
public:
    explicit CountDownLatch(int count);
    void wait();
    void countDown();
private:
    mutable std::mutex mutex_;
    std::condition_variable condition_;
    int count_;
};
