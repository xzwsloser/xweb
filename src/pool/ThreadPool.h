// @Author: loser
#pragma once
#include <atomic>
#include <condition_variable>
#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>
#include <memory>


namespace xweb {

class ThreadPool {
public:
  ThreadPool(int minThreads = 5,
             int maxThreads = std::thread::hardware_concurrency());
  ~ThreadPool();

  template <typename F, typename... Args>
  auto AddTask(F &&f, Args &&...args)
      -> std::future<typename std::result_of<F(Args...)>::type>;

  void Init();

private:
  void manager();
  void worker();

private:
  std::thread *manager_;
  std::pmr::unordered_map<std::thread::id, std::thread> workers_;
  std::vector<std::thread::id> exit_ids_;
  int min_threads_;
  int max_threads_;
  std::atomic<bool> stop_{false};
  std::atomic<int> cur_threads_;
  std::atomic<int> idle_threads_;
  std::atomic<int> exit_numbers_;
  std::queue<std::function<void()>> tasks_;
  std::mutex queue_mutex_;
  std::mutex ids_mutex_;
  std::condition_variable condition_;
};

template<typename F,typename... Args>
auto ThreadPool::AddTask(F&& f , Args&&... args)
    -> std::future<typename std::result_of<F(Args...)>::type>
{
    using resType = typename std::result_of<F(Args...)>::type;
    auto task = std::make_shared<std::packaged_task<resType()>>(std::bind(std::forward<F>(f) , std::forward<Args>(args)...));
    std::future<resType> res = task -> get_future(); 
    {
        std::unique_lock<std::mutex> lock { this -> queue_mutex_ };
        tasks_.emplace([task]() {
            (*task)(); 
        });
    }
    condition_.notify_all();
    return res;
}

}
