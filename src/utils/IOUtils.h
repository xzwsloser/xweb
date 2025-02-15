// @Author: loser
#pragma once

#include "errno.h"
#include "nocopyable.h"
#include <fcntl.h>
#include <signal.h>
#include <string>

class IOUtils: nocopyable {
public:
    // read n bytes from fd to buff
    static ssize_t readn(int fd, void *buff, size_t n);
    // if read successful
    static ssize_t readn(int fd, std::string &inBuffer, bool &zero);
    static ssize_t readn(int fd, std::string &inBuffer);
    static ssize_t writen(int fd, void *buff, size_t n);
    static ssize_t writen(int fd, std::string &inBuffer);
private:
    IOUtils() = delete;
    ~IOUtils() =delete;
};
