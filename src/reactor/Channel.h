// @Author loser
#pragma once
#include <functional>
#include <memory>
#include <string>
#include <sys/epoll.h>

class EventLoop;
/*class HttpConnection;*/

class Channel {
private:
  using CallBack = std::function<void()>;
  EventLoop *loop;
  int fd_;
  uint32_t events_;      // interested events
  uint32_t revents_;     // real events
  uint32_t last_events_; // last events;

  /*std::weak_ptr<HttpConnection> holder_; // connection obj*/

  CallBack readHandler_;
  CallBack writeHandler_;
  CallBack errorHandler_;
  CallBack connHandler_; // connection callback

  void handleRead();
  void handleWrite();
  void handleError();
  void handleConn();

public:
  Channel(EventLoop *loop);
  Channel(EventLoop *loop, int fd);
  ~Channel() ;

  void setFd(int fd);
  int getFd();
  /*void setHolder(std::shared_ptr<HttpConnection> holder);*/
  /*std::shared_ptr<HttpConnection> getHolder();*/
  void setRevents(uint32_t ev);
  void setEvents(uint32_t ev);
  uint32_t getEvents();
  uint32_t getLastEvents();

  void setReadHandler(CallBack &&readHandler);
  void setWriteHandler(CallBack &&writeHandler);
  void setErrorHandler(CallBack &&errorHandler);
  void setConnHandler(CallBack &&connHandler);

  bool equalAndUpdateLastEvents();

  void handleEvents(); // core method: handle events;
  /*void handleClose();  // handle the close event*/
};

using SP_Channel = std::shared_ptr<Channel>;
