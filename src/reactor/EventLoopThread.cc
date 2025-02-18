// @Author: loser
#include "EventLoopThread.h"
#include "../pool/MemoryPool.h"

namespace xweb {

EventLoopThread::EventLoopThread()
    :loop_(new EventLoop()),
     thread_(nullptr)
{

}


void EventLoopThread::deleteThread(std::thread* thread)
{
    if(thread -> joinable()) {
        thread -> join();
    }

    freeMemory(sizeof(std::thread) , reinterpret_cast<void*>(thread));
}

SP_EventLoop EventLoopThread::getLoop()
{
    return loop_;
}

void EventLoopThread::start()
{
    thread_.reset(new std::thread(std::bind(&EventLoopThread::threadFunc , this)));
}

void EventLoopThread::threadFunc()
{
    loop_-> loop();
}

EventLoopThread::~EventLoopThread()
{
    if(thread_ -> joinable()) {
        thread_ -> join();
    }
}

}
