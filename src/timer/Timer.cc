// @Author: loser
#include "Timer.h"
#include <cmath>
#include <queue>
#include <sys/time.h>
#include <unistd.h>

namespace xweb {

// timeout -> ms
TimerNode::TimerNode(std::shared_ptr<Channel> channel, int timeout)
    : deleted_(false), channel_(channel) {
  struct timeval now_time;
  gettimeofday(&now_time, nullptr);
  // the time is 0 - 9999
  expired_time_ =
      (((now_time.tv_sec % 10000) * 1000) + (now_time.tv_usec / 1000)) +
      timeout;
}

TimerNode::~TimerNode() {
  // TODO close the connection
  /*if(holder_ != nullptr) holder_ -> handleClose();*/
  /*if(channel_ != nullptr) channel_ -> handleClose();*/
}

TimerNode::TimerNode(TimerNode &tn) : channel_(tn.channel_), expired_time_(0) {}

void TimerNode::update(int timeout) {
  struct timeval now_time;
  gettimeofday(&now_time, nullptr);
  expired_time_ =
      ((now_time.tv_sec) % 10000) * 1000 + (now_time.tv_usec / 1000) + timeout;
}

bool TimerNode::isVaild() {
  struct timeval now_time;
  gettimeofday(&now_time, nullptr);
  size_t temp_time =
      (now_time.tv_sec % 10000) * 1000 + (now_time.tv_usec / 1000);
  if (temp_time < expired_time_) {
    return true;
  } else {
    this->setDeleted();
    return false;
  }
}

void TimerNode::clearReq() {
  channel_.reset();
  this->setDeleted();
}

void TimerManager::addTimer(std::shared_ptr<Channel> holder, int timeout) {
  SP_TimerNode new_timer_node{new TimerNode{holder, timeout}};
  timer_node_queue_.push(new_timer_node);
  // TODO HttpConection link the timer
  /*holder -> linkTimer();*/
}

void TimerManager::handleExpiredEvent() {
  while (!timer_node_queue_.empty()) {
    SP_TimerNode timer_node = timer_node_queue_.top();
    if (timer_node->isDeleted()) {
      timer_node_queue_.pop();
    } else if (!(timer_node->isVaild())) {
      timer_node_queue_.pop();
    } else {
      break;
    }
  }
}

} // namespace xweb
