#include "../../logger/Logger.h"
#include <chrono>
#include <iostream>
#include <thread>
using namespace std;
int main() {
  cout << "日志系统开始工作" << endl;
  LOG << "hello world" << '\n';
  LOG_DEBUG << "hello world";
  LOG_INFO << "hello world";
  LOG_ERROR << "hello world";
  LOG_ERROR << "hello world";
  LOG_FATAL << "hello world";
  cout << "日志系统结束工作" << endl;
  this_thread::sleep_for(chrono::seconds(5));
}
