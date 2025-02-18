// @Author: loser
#include "EventLoopThreadPool.h"
#include "../logger/Logger.h"
#include "MemoryPool.h"

namespace xweb {

EventLoopThreadPool::EventLoopThreadPool(std::shared_ptr<EventLoop> loop, int numThreads)
    : numThreads_(numThreads), index_(0), base_loop_(loop) {
  if (numThreads_ <= 0) {
    LOG_FATAL << "the number of numThreads < 0";
    abort();
  }

  threads_.reserve(numThreads_);
  for (int i = 0; i < numThreads_; i++) {
    std::shared_ptr<EventLoopThread> t(new EventLoopThread);
    threads_.emplace_back(t);
  }
}

void EventLoopThreadPool::start() {
  for (auto &thread : threads_) {
    thread->start();
  }
}

SP_EventLoop EventLoopThreadPool::getNextLoop() {
  index_ = (index_ + 1) % numThreads_;
  return threads_[index_]->getLoop();
}

} // namespace xweb
