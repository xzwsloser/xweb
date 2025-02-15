// @Author: loser
// users use the LogStream to write log to fronted
#pragma once
#include<string>
#include<cstring>
#include "../utils/nocopyable.h"

namespace xweb { 

constexpr int kSmallBufferSize = 4096;  // 4KB
constexpr int kLargeBufferSize = 4096 * 1024;  // 4MB                                    
                                               

// Buffer 
template<int SIZE>
class FixedBuffer: nocopyable {
public:
    FixedBuffer(): cur_(data_) {} 
    ~FixedBuffer() = default;
    
    const char* data() const { return data_; }
    int length() const { return static_cast<int>(cur_ - data_); };
    char* current() { return cur_; }
    
    int avaliable() const { return static_cast<int>(end() - cur_); }
    void add(size_t len) { cur_ += len; }

    void reset() { cur_ = data_; }
    void bzero() { memset(data_ , 0 , sizeof(data_)); }

    void append(const char* buf , size_t len)
    {
        if(avaliable() > static_cast<int>(len)) {
            memcpy(cur_ , buf , len); 
            cur_ += len;
        }
    }

private:
    char data_[SIZE];  // real data
    char* cur_; // cur Pointer                   
    const char* end() const { return data_ + sizeof(data_); }             
};

class LogStream: nocopyable {
public:
    using Buffer = FixedBuffer<kSmallBufferSize>;     

    LogStream() {}
    LogStream& operator<< (bool v) 
    {
        if(is_show_) {
            buffer_.append(v ? "1" : "0" , 1);
        }
        return *this;
    }

    LogStream& operator<< (short);
    LogStream& operator<< (unsigned short);
    LogStream& operator<< (unsigned int);
    LogStream& operator<< (int);
    LogStream& operator<< (long);
    LogStream& operator<< (unsigned long);
    LogStream& operator<< (long long);
    LogStream& operator<< (unsigned long long);
    LogStream& operator<< (float v)
    {
        *this << static_cast<double>(v);
        return *this;
    }

    LogStream& operator<< (double);
    LogStream& operator<< (long double);
    LogStream& operator<< (char v)
    {
        if(is_show_) {
            buffer_.append(&v , 1);
        }
        return *this;
    }

    LogStream& operator<< (const char* str)
    {
        if(is_show_) {
            if(str) {
                buffer_.append(str , strlen(str));
            } else {
                buffer_.append("(null)" , 6);
            }
        }
        return *this;
    }
LogStream& operator<< (const std::string& str)
    {
        if(is_show_) {
            buffer_.append(str.c_str() , str.size());
        }
        return *this;
    }

    void append(const char* data , int len)
    {
        buffer_.append(data , len);
    }

    const Buffer& buffer() const { return buffer_; }
    void resetBuffer() { buffer_.reset(); }

    void setShowAttr(bool v) { is_show_ = v; }
    /*bool outputLevel();*/
private:
    // cast and append
    template<typename T> 
    void append(T);

    Buffer buffer_; 
    // the max sizeof number output
    static const int kMaxNumericSize = 32;

    // show the log or not
    bool is_show_{true}; 
};

}
