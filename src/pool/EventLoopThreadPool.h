// @Author: loser
#pragma once
#include "../reactor/EventLoopThread.h"
#include "../reactor/EventLoop.h"
#include "../logger/Logger.h"

namespace xweb {

class EventLoopThreadPool {
public:
    EventLoopThreadPool(std::shared_ptr<EventLoop> loop , int numThreads);
    ~EventLoopThreadPool() { LOG_INFO << "~EventLoopThreadPool "; }

    void start();
    SP_EventLoop getNextLoop();

private:
    std::shared_ptr<EventLoop> base_loop_;
    int numThreads_;
    int index_;
    std::vector<std::shared_ptr<EventLoopThread>> threads_;
};

}
