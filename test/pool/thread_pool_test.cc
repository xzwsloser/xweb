// @Author: loser
#include "../../pool/ThreadPool.h"
#include <cmath>
#include <iostream>
#include <thread>
using namespace std;

int main() {
  ThreadPool *tp = new ThreadPool();
  auto f1 = tp->AddTask([](int a, int b) { return a * b; }, 1, 2);
  auto f2 = tp->AddTask([](int c) { return c * c * c * c; }, 3);
  auto f3 = tp->AddTask([](double d) { return M_PI * d * d; }, 3.2);
  cout << "Task1 结果: " << f1.get() << endl;
  cout << "Task2 结果: " << f2.get() << endl;
  cout << "Task3 结果: " << f3.get() << endl;
  delete tp;
  std::this_thread::sleep_for(std::chrono::seconds(2));
}
