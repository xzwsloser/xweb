#include "../../pool/MemoryPool.h"
#include <iostream>
#include <memory>
#include <thread>

using namespace std;

// 利用内存池管理 std::thread

static void deleteThread(thread *t) {
  if (t->joinable()) {
    t->join();
    cout << "析构函数执行完毕" << endl;
  }

  freeMemory(sizeof(thread), reinterpret_cast<void *>(t));
}

void threadFunc() {
  cout << "线程执行函数开始执行 ..." << endl;
  this_thread::sleep_for(2s);
  cout << "线程执行函数结束执行 ..." << endl;
}

int main() {
  unique_ptr<thread, decltype(&deleteThread)> thread_(nullptr, deleteThread);
  cout << "开启任务" << endl;
  thread_.reset(newElement<thread>(threadFunc));
}
