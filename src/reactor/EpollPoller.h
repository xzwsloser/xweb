// @Author: loser
// Poller using epoll
#pragma once
#include "Channel.h"
#include "../timer/Timer.h"
#include <unordered_map>
#include <vector>

class EpollPoller {
public:
  EpollPoller();
  ~EpollPoller() {};

  void epollAdd(const SP_Channel &request , int timeout);
  void epollMod(const SP_Channel &request , int timeout);
  void epollDel(const SP_Channel &request);

  void epollDel(int fd);  
  void addTimer(std::shared_ptr<Channel> holder , int timeout);

  // core Method, wait and fill the events group
  void poll(std::vector<SP_Channel> &req);

  int getEpollFd() { return epoll_fd_; }
  void handleExpired();

private:
  int epoll_fd_;                                    // epoll FD
  std::vector<epoll_event> events_;                 // really events
  std::unordered_map<int, SP_Channel> channel_map_; // fd -> Channel //
  TimerManager timer_manager_;                                                   
};
