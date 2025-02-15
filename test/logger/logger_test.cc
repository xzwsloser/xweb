// @Author: loser
// 测试日志系统
#include "../../src/logger/Logger.h"
#include <chrono>
#include <thread>
#include <vector>
using namespace std;
using namespace xweb;

void threadFunc(int i) {
  for (int i = 0; i < 10000; i++) {
      LOG << "thread" << i << " get " << i << '\n';
  }
}

int main() {
  cout << "日志系统开始工作" << endl;
  vector<thread> ts;
  for (int i = 0; i < 10; i++) {
    ts.emplace_back(threadFunc, i + 1);
  }

  for (int i = 0; i < 10; i++) {
    ts[i].join();
  }

  cout << "日志系统结束工作" << endl;
  // wait the back_end thread work finished!
  this_thread::sleep_for(chrono::seconds(30));
}
