// @Author: loser
#include "CountDownLatch.h"
#include <mutex>

namespace xweb {

CountDownLatch::CountDownLatch(int count): 
    count_(count) {}
   
void CountDownLatch::wait()
{
    std::unique_lock<std::mutex> lock { mutex_ };
    // condition_variable wait the condition true
    // so this -> count_ <= 0 is OK
    condition_.wait(lock , [this]() -> bool { return this -> count_ <= 0; });
}

void CountDownLatch::countDown()
{
    std::lock_guard<std::mutex> lock { mutex_ };
    count_--;
    if(count_ == 0) condition_.notify_all();
}

}
