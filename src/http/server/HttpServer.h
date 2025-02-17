// @Author: loser
#pragma once
#include "HttpGroup.h"
#include "../context/HttpContext.h"
#include "../../server/TcpServer.h"
#include "../../reactor/Channel.h"
#include "../../pool/ThreadPool.h"
#include <memory>
#define DEFAULT_THREAD_NUM 5

namespace xweb {

class HttpServer: public HttpGroup {
public:
    HttpServer(): HttpGroup("") , server_() , channel_(new Channel()) , pool_(new ThreadPool()) {}
    void Run(int port);
private:
    TcpServer server_;
    std::shared_ptr<Channel> channel_;
    std::shared_ptr<ThreadPool> pool_;
    void NewEvent(int fd , SP_EventLoop loop);

    void handleRead();
    void handleWrite();
    void handleError();
    void handleConn();
    void handleClose();

    void RealHandler();

};

}
