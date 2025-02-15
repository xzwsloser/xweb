// @Author: loser
#include "../logger/Logger.h"
#include "EpollPoller.h"
#include <cassert>
#include <sys/epoll.h>

const int EVENTSUM = 4096; // events number
const int EPOLLWAIT_TIME = 1000;                        

EpollPoller::EpollPoller()
    : epoll_fd_(epoll_create1(EPOLL_CLOEXEC)), events_(EVENTSUM) {
  assert(epoll_fd_ > 0);
}

void EpollPoller::epollAdd(const SP_Channel& request , int timeout)
{
    int fd = request -> getFd(); 
    channel_map_[fd] = request;

    if(timeout > 0) {
        addTimer(request , timeout);
    }

    request -> equalAndUpdateLastEvents();

    struct epoll_event event;
    event.data.fd = fd;
    event.events = request -> getEvents();
    if(epoll_ctl(epoll_fd_ , EPOLL_CTL_ADD , fd , &event) < 0) {
        /*perror("epoll add failed!");*/
        LOG_ERROR << "epoll add failed!";
        channel_map_[fd].reset();
    }
}

void EpollPoller::epollMod(const SP_Channel& request , int timeout)
{
    if(timeout > 0) addTimer(request , timeout);
    int fd = request -> getFd();
    if(!(request -> equalAndUpdateLastEvents())) {
        channel_map_[fd] -> setEvents(request -> getEvents());
        struct epoll_event event;
        event.data.fd = fd;
        event.events = request -> getEvents();
        if(epoll_ctl(epoll_fd_ , EPOLL_CTL_MOD , fd , &event) < 0) {
            /*perror("epollMod failed!");*/
            LOG_ERROR << "epollMod failed!";
            channel_map_[fd].reset();
        }
    }
}

void EpollPoller::epollDel(const SP_Channel& request)
{
    int fd  = request -> getFd();
    epollDel(fd);
}

void EpollPoller::epollDel(int fd)
{
     if(!channel_map_[fd]) {
       channel_map_[fd].reset(); 
       if(epoll_ctl(epoll_fd_ , EPOLL_CTL_DEL , fd , nullptr) < 0) {
           /*perror("epollDel failed!");*/
           LOG_ERROR << "epollDel failed!";
       }
    }
}

void EpollPoller::poll(std::vector<SP_Channel>& req)
{
    int event_num = epoll_wait(epoll_fd_ , 
            &(*events_.begin()) , EVENTSUM , EPOLLWAIT_TIME );
    for(int i = 0 ; i < event_num ; i ++) {
        SP_Channel temp = channel_map_[events_[i].data.fd];
        if(temp) {
            temp -> setRevents(events_[i].events);
            req.emplace_back(std::move(temp));
        }
    }
}

void EpollPoller::handleExpired()
{
    timer_manager_.handleExpiredEvent();
}

void EpollPoller::addTimer(SP_Channel holder , int timeout)
{
    if(holder != nullptr) {
        timer_manager_.addTimer(holder , timeout);
    } else {
        LOG_ERROR << "timer add failed!";
    }
}
