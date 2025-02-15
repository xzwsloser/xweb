// @Author: loser
#include "LogFile.h"
#include<mutex>

namespace xweb {

LogFile::LogFile(const std::string& base_name , int flushEvenryN_):
    base_name_(base_name),
    flushEvenryN_(flushEvenryN_),
    cur_flush_times_(0),
    mutex_(new std::mutex)
{
    file_.reset(new AppendFile(base_name_));
}

void LogFile::append(const char* log_line , size_t len)
{
    std::lock_guard<std::mutex> lock { *mutex_ };
    append_unlocked(log_line , len);
}

void LogFile::append_unlocked(const char* log_line , size_t len)
{
    file_-> append(log_line , len); // write into file buffer
    cur_flush_times_++;                                    
    if(cur_flush_times_ >= flushEvenryN_)
    {
        cur_flush_times_ = 0;
        file_->flush();
    }
}

void LogFile::flush()
{
    std::lock_guard<std::mutex> lock{ *mutex_ };
    file_->flush();
}

}
