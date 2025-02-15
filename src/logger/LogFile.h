// @Author: loser
#pragma once
#include "../utils/FileUtil.h"
#include "../utils/nocopyable.h"
#include<mutex>
#include<memory>


namespace xweb {

class LogFile: nocopyable {
public:
    LogFile(const std::string& base_name , int flushEveryN = 1024); 
    ~LogFile() = default;

    void append(const char* log_line , size_t len);
    void flush();
    bool rollFile();
private:
    void append_unlocked(const char* log_line , size_t len);

    const std::string base_name_;
    const int flushEvenryN_;

    int cur_flush_times_;  
    std::unique_ptr<std::mutex> mutex_;
    std::unique_ptr<AppendFile> file_;
};

}
