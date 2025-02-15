// @Author: loser
#include "FileUtil.h"
#include<stdio.h>

namespace xweb {

AppendFile::AppendFile(std::string file_name):
    fp_(fopen(file_name.c_str() , "a")) 
{
    // set stream default buffer to buffer
    setbuffer(fp_ , buffer_ , sizeof(buffer_));
}

AppendFile::~AppendFile()
{
    fclose(fp_);
}

size_t AppendFile::write(const char* log_line , size_t len)
{
    // fwrite without lock to enable thread security
    return fwrite_unlocked(log_line , 1 , len , fp_);    
}

// write the log from buffer to file
void AppendFile::flush()
{
    fflush(fp_);
}

// append logline to buffer
void AppendFile::append(const char* log_line , size_t len)
{
    size_t nread = this -> write(log_line , len);
    size_t nleft = len - nread;
    while(nleft > 0) {
        size_t x = this -> write(log_line + nread , nleft);
        if(x == 0) {
            // Check last operation is or not error
            int err = ferror(fp_);
            if(err) fprintf(stderr , "AppendFile::append() failed!\n");
            break;
        }
        nread += x;
        nleft = len - nread;
    }
}

}
