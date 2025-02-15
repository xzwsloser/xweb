// @Author: loser
#include "TcpServer.h"
#include "../utils/SocketUtils.h"
#include<sys/socket.h>
#include<arpa/inet.h>
#include<utility>
#include<cstring>
#include<memory>

TcpServer::TcpServer(EventLoop* loop , int threadNum , int port)
    : loop_(loop),
      thread_num_(threadNum),
      event_loop_thread_pool_(new EventLoopThreadPool(loop_ , threadNum)),
      accept_channel_(new Channel(loop_)),
      port_(port),
      listen_fd_(SocketUtils::socketBindListen(port_))
{
    accept_channel_ -> setFd(listen_fd_);
    SocketUtils::ignoreSigPipe(); 
    if(SocketUtils::setSocketNoBlocking(listen_fd_) < 0) {
        LOG_ERROR << "set socket no block failed";
        abort();
    }
}

void TcpServer::start()
{
    event_loop_thread_pool_ -> start();
    accept_channel_ -> setEvents(EPOLLIN | EPOLLET);
    accept_channel_ -> setReadHandler(std::bind(&TcpServer::handleNewConn , this)); 
    accept_channel_ -> setConnHandler(std::bind(&TcpServer::handleThisConn , this));
    loop_ -> pollerAdd(accept_channel_ , 0);
    started_ = true;
}

void TcpServer::handleNewConn()
{
    struct sockaddr_in client_addr;
    memset(&client_addr , 0 , sizeof(client_addr));
    socklen_t client_addr_len = sizeof(client_addr);
    int accept_fd = 0;
    while((accept_fd = accept(listen_fd_ , (struct sockaddr*)&client_addr , &client_addr_len)) > 0) {
        std::shared_ptr<EventLoop> loop = event_loop_thread_pool_ -> getNextLoop(); 
        LOG_INFO << "New connection from " << inet_ntoa(client_addr.sin_addr) << ":" << ntohs(client_addr.sin_port); 

        if(accept_fd >= MAXFDS) {
            close(accept_fd);
            continue;
        }

        if(SocketUtils::setSocketNoBlocking(accept_fd) < 0) {
            LOG_ERROR << "set no block failed!";
            return ;
        }
        callback_(accept_fd , loop);
    }
    accept_channel_ -> setEvents(EPOLLIN | EPOLLOUT); 
}
