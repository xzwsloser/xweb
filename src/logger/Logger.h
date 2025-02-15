// @Author: loser
#pragma once
#include "LogStream.h"
#include <functional>
#include<stdio.h>
#include<iostream>
#include "AsyncLogger.h"

enum class logger_level: unsigned int { DEBUG , INFO , WARN , ERROR , FATAL};

class Logger {
public:
    Logger(const char* file_name , int line);
    Logger(const char* file_name , int line , logger_level cur_level);
    Logger(const char* file_name , int line , logger_level cur_level , logger_level level);
    ~Logger(); 

    LogStream& stream() { return impl_.stream_; };

    static void setLogFileName(std::string fileName) { logFileName_ = fileName; }
    static std::string getLogFileName() { return logFileName_; }

private:
    class Impl {
    public:
        Impl(const char* file_name , int line);
        Impl(const char* file_name , int line , logger_level cur_level);
        Impl(const char* file_name , int line , logger_level cur_level , logger_level level);
        void formatTime();

        LogStream stream_;
        int line_;
        std::string basename_;
        logger_level cur_level_{logger_level::INFO};
        logger_level max_level_{logger_level::INFO};
    };

    Impl impl_;
    static std::string logFileName_;
};

#define LOG  Logger(__FILE__, __LINE__).stream()
#define LOG_DEBUG Logger(__FILE__,__LINE__,logger_level::DEBUG).stream()
#define LOG_INFO Logger(__FILE__,__LINE__,logger_level::INFO).stream()
#define LOG_WARN Logger(__FILE__,__LINE__,logger_level::WARN).stream()
#define LOG_ERROR Logger(__FILE__,__LINE__,logger_level::ERROR).stream()
#define LOG_FATAL Logger(__FILE__,__LINE__,logger_level::FATAL).stream()
