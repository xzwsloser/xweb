// @Author: loser
#include "LogStream.h"
#include <cstdio>

/*constexpr char digits[] = "9876543210123456789"; */
/*const char* zero = digits + 9;*/
/**/
/*template<typename T>*/
/*size_t convert(char buf[] , T value)*/
/*{*/
/*    T val = value;*/
/*    char* p = buf;*/
/**/
/*    do {*/
/*        int lsd = static_cast<int>(val % 10);*/
/*        val /= 10;*/
/*        *p++ = zero[lsd]; */
/*    } while (val != 0);*/
/*}*/

template<typename T>
void LogStream::append(T value)
{
    if(is_show_) {
        if(buffer_.avaliable() >= kMaxNumericSize) {
            *this << std::to_string(value);
        }
    }
}

/*bool LogStream::outputLevel()*/
/*{*/
/*    if(cur_level_ < level_) {*/
/*        return false; */
/*    }*/
/**/
/*    const char* level_message = "[DEBUG]";*/
/*    if(level_ == logger_level::INFO) {*/
/*        level_message = "[INFO]";*/
/*    } else if(level_ == logger_level::WARN) {*/
/*        level_message = "[WARN]";*/
/*    } else if(level_ == logger_level::ERROR) {*/
/*        level_message = "[ERROR]";*/
/*    } else if(level_ == logger_level::FATAL) {*/
/*        level_message = "[FATAL]";*/
/*    }*/
/**/
/*    buffer_.append(level_message , strlen(level_message));*/
/*    return true;*/
/*}*/

LogStream& LogStream::operator<< (short v)
{
    *this << static_cast<int>(v);
    return *this;
}

LogStream& LogStream::operator<< (unsigned short v)
{
    *this << static_cast<unsigned int>(v);
    return *this;
}

LogStream& LogStream::operator << (int v)
{
    append<int>(v);
    return *this;
}

LogStream& LogStream::operator<< (unsigned int v)
{
    append<unsigned int>(v);
    return *this;
}

LogStream& LogStream::operator<< (long v)
{
    append<long>(v);
    return *this;
}

LogStream& LogStream::operator<< (unsigned long v) 
{
    append<unsigned long>(v);
    return *this;
}

LogStream& LogStream::operator<< (long long v)
{
    append<long long>(v);
    return* this;
}

LogStream& LogStream::operator<< (double v)
{
    if(is_show_) {
        if(buffer_.avaliable() >= kMaxNumericSize)
        {
            int len = snprintf(buffer_.current() , kMaxNumericSize , "%.12g" , v);
            buffer_.add(len);
        }
    }

    return *this;
}

LogStream& LogStream::operator<< (long double v)
{
    if(is_show_) {
        if(buffer_.avaliable() >= kMaxNumericSize)
        {
            int len = snprintf(buffer_.current(), kMaxNumericSize, "%.12Lg" , v);
            buffer_.add(len);
        }
    }
    return *this;
}


