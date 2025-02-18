// @Author: loser
#pragma once
#include "EventLoop.h"
#include <memory>
#include <thread>

namespace xweb {

using SP_EventLoop = std::shared_ptr<EventLoop>;

class EventLoopThread {
public:
  EventLoopThread();
  EventLoopThread(SP_EventLoop loop): loop_(loop) , thread_(nullptr){}
  ~EventLoopThread();

  // start the event loop
  void start();
  // get the pointer to eventLoop
  SP_EventLoop getLoop();
  // the deletetor of std::thread
private:
  static void deleteThread(std::thread *thread);
  // please pay attention to this function used to event loop
  // log sys is different
  void threadFunc();
  SP_EventLoop loop_;
  std::unique_ptr<std::thread> thread_;
};

} // namespace xweb
