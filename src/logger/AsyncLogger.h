// @Author: loser
#pragma once
#include "LogStream.h"
#include "../utils/nocopyable.h"
#include "../utils/CountDownLatch.h"
#include<thread>
#include<mutex>
#include<condition_variable>
#include<vector>
#include<memory>

class AsyncLogger: nocopyable {
public:
    AsyncLogger(const std::string base_name , int flushInterval = 2);
    ~AsyncLogger();

    void append(const char* log_line , size_t len);
    void start();
    void stop();

private:
    void threadFunc(); // thread callback function
    using Buffer = FixedBuffer<kLargeBufferSize>;                    
    using BufferVector = std::vector<std::shared_ptr<Buffer>>;
    using BufferPtr = std::shared_ptr<Buffer>;

    const int flushInterval_;
    bool is_running_;
    std::string base_name_;
    std::thread thread_; // write thread
    std::mutex mutex_;                      
    std::condition_variable condition_;
    BufferPtr currentBuffer_;
    BufferPtr nextBuffer_;
    BufferVector buffers_; CountDownLatch latch_; 
};
