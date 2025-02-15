// @Author: loser
#include "ThreadPool.h"
#include <functional>
#include <chrono>
#include "../logger/Logger.h"

namespace xweb {

ThreadPool::ThreadPool(int minThreads, int maxThreads)
    : min_threads_(minThreads), max_threads_(maxThreads), stop_(false),
      exit_numbers_(0) {
  idle_threads_ = cur_threads_ = minThreads;
  manager_ = new std::thread{&ThreadPool::manager, this};
  for (int i = 0; i < cur_threads_; i++) {
    std::thread t{&ThreadPool::worker, this};
    workers_.insert({t.get_id(), std::move(t)});
  }
}

ThreadPool::~ThreadPool() {
  stop_ = true;
  condition_.notify_all();

  for (auto &it : workers_) {
    std::thread &t = it.second;
    if (t.joinable()) {
      t.join();
      LOG_INFO << "worker is destoryed!";
    }
  }

  if (manager_->joinable()) {
    manager_->join();
    LOG_INFO << "manager is destoryed!";
  }

  delete manager_;
}

void ThreadPool::worker() {
  while (!stop_) {
    std::function<void()> task;
    {
      std::unique_lock<std::mutex> lock{this->queue_mutex_};
      condition_.wait(
          lock, [this]() { return this->stop_ || !(this->tasks_.empty()); });
      if (exit_numbers_.load() > 0) {
        exit_numbers_--;
        cur_threads_--;
        std::unique_lock<std::mutex> ids_lock{this->ids_mutex_ };
        exit_ids_.emplace_back(std::this_thread::get_id());
        return;
      }

      if(stop_ && tasks_.empty()) {
          return ;
      }

      if (!tasks_.empty()) {
        task = std::move(tasks_.front());
        tasks_.pop();
      }
    }

    if(task != nullptr) {
        idle_threads_--;
        task();
        idle_threads_++;
    }
  }
}

void ThreadPool::manager()
{
    while(!stop_) {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        int idle = idle_threads_.load();
        int current = cur_threads_.load();
        if(idle > current / 2 && current > min_threads_) {
            exit_numbers_.store(2);
            condition_.notify_all();
            std::unique_lock<std::mutex> ids_lock{this->ids_mutex_ };
            for(const auto& id : exit_ids_) {
                auto it = workers_.find(id);
                if(it != workers_.end()) {
                    (it -> second).join(); 
                    workers_.erase(it);
                }
            } 
            exit_ids_.clear();
        }

        else if(idle == 0 && current < max_threads_) {
            std::thread t{&ThreadPool::worker , this};
            workers_.insert({t.get_id() , std::move(t)});
            cur_threads_++;
            idle_threads_++;
        }
    }
}
}
