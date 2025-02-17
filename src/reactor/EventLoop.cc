// @Author: loser
#include "EventLoop.h"
#include "../logger/Logger.h"
#include "../utils/IOUtils.h"
#include "Channel.h"
#include "EpollPoller.h"
#include "sys/socket.h"
#include "unistd.h"
#include <cassert>
#include <memory>
#include <sys/eventfd.h>
#include<iostream>
#include <vector>

namespace xweb {

int EventLoop::createEventfd() {
  int evfd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
  if (evfd < 0) {
    /*perror("Failed in eventfd!");*/
    LOG_ERROR << "Failed in eventfd!";
    abort();
  }
  return evfd;
}

EventLoop::EventLoop()
    : poller_(new EpollPoller()), wake_up_fd_(createEventfd()),
      wake_up_channel_(new Channel(this, wake_up_fd_)), is_looping_(false),
      is_quit_(false), is_event_handling_(false)
{
  wake_up_channel_->setEvents(EPOLLIN | EPOLLET);
  wake_up_channel_->setReadHandler(std::bind(&EventLoop::handleRead, this));
  wake_up_channel_->setConnHandler(std::bind(&EventLoop::handleConn, this));
  poller_->epollAdd(wake_up_channel_, 0);
}

EventLoop::~EventLoop() { close(wake_up_fd_); }

/**/
/*bool EventLoop::isInLoopThread() {*/
/*  return thread_id_ == std::this_thread::get_id();*/
/*}*/

void EventLoop::pollerAdd(std::shared_ptr<Channel> channel, int timeout) {
  poller_->epollAdd(channel, timeout);
}

void EventLoop::pollerDel(std::shared_ptr<Channel> channel) {
  poller_->epollDel(channel);
}

void EventLoop::pollerDel(int fd) { poller_->epollDel(fd); }

void EventLoop::pollerMod(std::shared_ptr<Channel> channel, int timeout) {
  poller_->epollMod(channel, timeout);
}

/*void EventLoop::runInLoop(Function &&func) {*/
/*    func();*/
/*}*/

/*void EventLoop::queueInLoop(Function &&func) {*/
/*  // the pending_functions_ is a task queue*/
/*  {*/
/*    std::lock_guard<std::mutex> lock{mutex_};*/
/*    pending_functions_.emplace_back(std::move(func));*/
/*  }*/
/**/
/*  if (!isInLoopThread() || is_calling_pending_functions_) {*/
/*    this->wakeup();*/
/*  }*/
/*}*/

void EventLoop::handleConn() { this->pollerMod(wake_up_channel_, 0); }

void EventLoop::wakeup() {
  uint64_t signal = 1;
  ssize_t n = IOUtils::writen(wake_up_fd_, &signal, sizeof(signal));
  if (n != sizeof(signal)) {
    /*std::cout << "EventLoop::wakeup write " << n << "bytes" << std::endl;*/
    LOG_INFO << "EventLoop::wakeup write" << n << " bytes";
  }
}

void EventLoop::handleRead() {
  uint64_t res = 1;
  ssize_t n = IOUtils::readn(wake_up_fd_, &res, sizeof(res));
  if (n != sizeof(res)) {
    /*std::cout << "EventLoop::handleRead reads " << n << " bytes" <<
     * std::endl;*/
    LOG_INFO << "EventLoop::handleRead reads " << n << " bytes";
  }
  wake_up_channel_->setEvents(EPOLLIN | EPOLLET);
}

void EventLoop::loop() {
  assert(!is_looping_);
  /*assert(isInLoopThread());*/
  is_looping_ = true;
  is_quit_ = false;
  std::vector<SP_Channel> ready_channel;
  while (!is_quit_) {
    ready_channel.clear();
    poller_->poll(ready_channel);
    is_event_handling_ = true;
    for (auto &it : ready_channel) {
      it->handleEvents();
    }
    is_event_handling_ = false;

    /*this->doPendingFunctions();*/
    poller_->handleExpired();
  }
  is_looping_ = false;
}

/*void EventLoop::doPendingFunctions() {*/
/*  std::vector<Function> functions;*/
/*  is_calling_pending_functions_ = true;*/
/*  {*/
/*    std::lock_guard<std::mutex> lock{this->mutex_};*/
/*    functions.swap(pending_functions_);*/
/*  }*/
/**/
/*  for (size_t i = 0; i < functions.size(); i++) {*/
/*    functions[i]();*/
/*  }*/
/**/
/*  is_calling_pending_functions_ = false;*/
/*}*/

void EventLoop::stopLoop() {
  is_quit_ = true;
}

void EventLoop::shutDown(std::shared_ptr<Channel> channel) {
  shutdown(channel->getFd(), SHUT_WR);
}

}
