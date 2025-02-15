// @Author loser
#include "Channel.h"
#include <sys/epoll.h>
#include<unistd.h>
#include "EventLoop.h"

Channel::Channel(EventLoop *loop)
    : loop(loop), revents_(0), events_(0), last_events_(0) {}

Channel::Channel(EventLoop *loop, int fd)
    : loop(loop), revents_(0), events_(0), last_events_(0), fd_(fd) {}


Channel::~Channel()
{
    close(fd_);
    loop->pollerDel(fd_);
}

void Channel::setFd(int fd) { this->fd_ = fd; }

int Channel::getFd() { return this->fd_; }


/*void Channel::setHolder(std::shared_ptr<HttpConnection> holder) {*/
/*  this->holder_ = std::weak_ptr<HttpConnection>(holder);*/
/*}*/
/**/
/*std::shared_ptr<HttpConnection> Channel::getHolder() {*/
/*  std::shared_ptr<HttpConnection> holder = holder_.lock();*/
/*  return holder;*/
/*}*/

void Channel::setRevents(uint32_t ev) { revents_ = ev; }

void Channel::setEvents(uint32_t ev) { events_ = ev; }

uint32_t Channel::getLastEvents() { return last_events_; }

uint32_t Channel::getEvents() { return events_; }

void Channel::setReadHandler(CallBack &&readHandler) {
  readHandler_ = std::move(readHandler);
}

void Channel::setWriteHandler(CallBack &&writeHandler) {
  writeHandler_ = std::move(writeHandler);
}

void Channel::setErrorHandler(CallBack &&errorHandler) {
  errorHandler_ = std::move(errorHandler);
}

void Channel::setConnHandler(CallBack &&connHandler) {
  connHandler_ = std::move(connHandler);
}

void Channel::handleRead() {
  if (readHandler_) {
    readHandler_();
  }
}

void Channel::handleWrite() {
  if (writeHandler_) {
    writeHandler_();
  }
}

void Channel::handleError() {
  if (errorHandler_) {
    errorHandler_();
  }
}

void Channel::handleConn() {
  if (connHandler_) {
    connHandler_();
  }
}

/*void Channel::handleClose()*/
/*{*/
/*    close(fd_);*/
/*    std::shared_ptr<Channel> del_channel(new Channel(loop , fd_));*/
/*    loop-> pollerDel(del_channel);*/
/*}*/

// core Method: handle Events
void Channel::handleEvents() {
  // connection closed
  // EPOLLPRI: emerge data come
  // EPOLLHUP: close connection
  // EPOLLRDHUP: close write
  if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
    events_ = 0;
    return;
  }

  if (revents_ & EPOLLERR) {
    handleError();
  }

  if (revents_ & EPOLLOUT) {
    handleWrite();
  }

  if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
    handleRead();
  }

  handleConn();
}

bool Channel::equalAndUpdateLastEvents() {
  bool ret = (events_ == last_events_);
  last_events_ = events_;
  return ret;
}
