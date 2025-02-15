// @Author: loser
#pragma once
#include<string>
#include "nocopyable.h"

namespace xweb {

class AppendFile: nocopyable {
public:
    explicit AppendFile(std::string file_name);
    ~AppendFile();

    // write from buffer to file(fronted to backend)
    void append(const char* log_line , const size_t len);   
    // flush into flash
    void flush();
private:
    size_t write(const char* log_line , size_t len);
    FILE* fp_;
    char buffer_[64 * 1024];  // 64KB
};

}
