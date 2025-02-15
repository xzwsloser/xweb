// @Author: loser #pragma once
#include <deque>
#include <memory>
#include <queue>
#include <unistd.h>
#include "../reactor/Channel.h"

/*class HttpConnection;*/

class TimerNode {
public:
  /*TimerNode(std::shared_ptr<HttpConnection> holder, int timeout);*/
  TimerNode(std::shared_ptr<Channel> channel , int timeout);
  ~TimerNode();
  TimerNode(TimerNode &tn);
  void update(int timeout);
  bool isVaild();
  void clearReq();
  void setDeleted() { deleted_ = true; }
  bool isDeleted() const { return deleted_; }
  size_t getExpireTime() const { return expired_time_; };

private:
  bool deleted_;
  size_t expired_time_;
  /*std::shared_ptr<HttpConnection> holder_;*/
  std::shared_ptr<Channel> channel_;
};

struct TimerCmp {
  bool operator()(std::shared_ptr<TimerNode> &ta,
                  std::shared_ptr<TimerNode> &tb) const {
    return ta->getExpireTime() > tb->getExpireTime();
  }
};

class TimerManager {
public:
  TimerManager() = default;
  ~TimerManager() = default;
  void addTimer(std::shared_ptr<Channel> holder, int timeout);
  // the method to handle expired event
  void handleExpiredEvent();

private:
  using SP_TimerNode = std::shared_ptr<TimerNode>;
  // the timer min heap
  std::priority_queue<SP_TimerNode, std::deque<SP_TimerNode>, TimerCmp>
      timer_node_queue_;
};
