// @Author: loser
#include "EventLoopThread.h"
#include "../pool/MemoryPool.h"

EventLoopThread::EventLoopThread()
    :loop_(newElement<EventLoop>() , deleteElement<EventLoop>),
     thread_(nullptr , deleteThread)
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
    thread_.reset(newElement<std::thread>(std::bind(&EventLoopThread::threadFunc , this)));
}

void EventLoopThread::threadFunc()
{
    loop_-> loop();
}
