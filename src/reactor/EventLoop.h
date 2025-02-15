// @Author: loser
#pragma once
#include "Channel.h"
#include "EpollPoller.h"
#include "sys/eventfd.h"
#include <mutex>
#include <thread>

class EventLoop {
public:
  using Function = std::function<void()>;
  EventLoop();
  ~EventLoop();

  // core method: event loop
  void loop();
  void stopLoop();

  // if this thread associated with this eventloop -> func
  // else -> In queue
  void runInLoop(Function &&func);
  void queueInLoop(Function &&func);

  void pollerAdd(std::shared_ptr<Channel> channel , int timeout = 0);
  void pollerMod(std::shared_ptr<Channel> channel , int timeout = 0);
  void pollerDel(std::shared_ptr<Channel> channel);
  void pollerDel(int fd);

  void shutDown(std::shared_ptr<Channel> channel);
  bool isInLoopThread();

private:
  static int createEventfd();

  std::shared_ptr<EpollPoller> poller_; // Poller In Loop
  int wake_up_fd_;                      // the wake up fd to wake up the subLoop
  mutable std::mutex mutex_;
  std::vector<Function> pending_functions_; // functions to do
  const std::thread::id thread_id_;
  std::shared_ptr<Channel> wake_up_channel_;

  bool is_looping_;
  bool is_quit_;
  bool is_event_handling_;
  bool is_calling_pending_functions_;

  void wakeup();
  void handleRead();
  void doPendingFunctions();
  void handleConn();
};
