// @Author: loser
#include "Logger.h"
#include "AsyncLogger.h"
#include "LogStream.h"
#include <algorithm>
#include <mutex>
#include<time.h>
#include<sys/time.h>

namespace xweb {

static std::once_flag flag;
static AsyncLogger* AsyncLogger_;

// static variable shoule be initialized outside the class
std::string Logger::logFileName_ = "./WebServer.log";

void once_init()
{
    AsyncLogger_ = new AsyncLogger(Logger::getLogFileName());
    AsyncLogger_ -> start();  // back_end thread start
}

void output(const char* msg , int len)
{
    std::call_once(flag , once_init);
    AsyncLogger_ -> append(msg , len);
}

Logger::Impl::Impl(const char* fileName , int line)
    : stream_(),
      line_(line),
      basename_(fileName)
{
    formatTime();
}

Logger::Impl::Impl(const char* fileName , int line , logger_level cur_level)
    : stream_(),
      line_(line),
      basename_(fileName),
      cur_level_(cur_level)
{
    formatTime();
}

Logger::Impl::Impl(const char* fileName , int line , logger_level cur_level , logger_level level)
    : stream_(),
      line_(line),
      basename_(fileName),
      cur_level_(cur_level),
      max_level_(level)
{
    formatTime();
}

void Logger::Impl::formatTime()
{

    if(cur_level_ >= max_level_) {
        const char* levelMes = "[DEBUG]";
        if(cur_level_ == logger_level::INFO) {
            levelMes = "[INFO]";
        } else if(cur_level_ == logger_level::WARN) {
            levelMes = "[WARN]";
        } else if(cur_level_ == logger_level::ERROR) {
            levelMes = "[ERROR]";
        } else if(cur_level_ == logger_level::FATAL) {
            levelMes = "[FATAL]";
        }
        
        stream_ << levelMes << '\t';
    } else {
        stream_.setShowAttr(false);
    }

    struct timeval tv;
    time_t time;
    char str_t[26]{0};
    gettimeofday(&tv , nullptr);
    time = tv.tv_sec;
    struct tm* p_time = localtime(&time);
    strftime(str_t, 26, "%Y-%m-%d %H:%M:%S\t\t",p_time); 
    stream_ << str_t;
}

Logger::Logger(const char* fileName , int line):
    impl_(fileName , line)
{

}

Logger::Logger(const char* fileName , int line , logger_level cur_level):
   impl_(fileName , line , cur_level) 
{

}

Logger::Logger(const char* fileName , int line , logger_level cur_level , logger_level level):
    impl_(fileName , line , cur_level , level)
{

}

Logger::~Logger()
{
    impl_.stream_ << "\t\t" << impl_.basename_ << impl_.line_ << '\n';
    const LogStream::Buffer& buf{ stream().buffer() };
    output(buf.data() , buf.length());
}

}
