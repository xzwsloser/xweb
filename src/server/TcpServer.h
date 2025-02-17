// @Author: loser
#pragma once
#include "../reactor/Channel.h"
#include "../reactor/EventLoop.h"
#include "../pool/EventLoopThreadPool.h"

namespace xweb {

class TcpServer {
public:
    using CallBack = std::function<void(int , SP_EventLoop)>;

    TcpServer() = default;
    TcpServer(EventLoop* loop , int threadNum , int port);
    ~TcpServer() = default;
    TcpServer(const TcpServer&) = delete;
    TcpServer& operator=(const TcpServer&) = delete;

    void Init(int threadNum , int port); 
    std::shared_ptr<EventLoop> getLoop() const { return loop_; }
    void start();
    void handleNewConn();
    void handleThisConn() { loop_->pollerMod(accept_channel_); }
    void setCallBack(std::function<void(int,SP_EventLoop)>&& cb) { callback_ = std::move(cb); }
private:
    static constexpr int MAXFDS = 100000;
    std::shared_ptr<EventLoop> loop_;
    int thread_num_;
    std::unique_ptr<EventLoopThreadPool> event_loop_thread_pool_;
    bool started_;
    std::shared_ptr<Channel> accept_channel_;
    int port_;
    int listen_fd_;
    // the callback function to handle the new connection
    CallBack callback_;
};

}
