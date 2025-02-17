// @Author: loser
#pragma once
#include<string>

namespace xweb {

class SocketUtils {
public:
    SocketUtils() = delete;
    ~SocketUtils() = delete;

    static void ignoreSigPipe();
    static int setSocketNoBlocking(int fd);
    static int socketBindListen(int port);
    static int Read(int fd , std::string& buffer , size_t size);
    static int Read(int fd , char* buffer , size_t size);
    static int Write(int fd , const std::string& buffer , size_t size);
    static int Write(int fd , const char* buffer , size_t size);
    static int ReadUntil(int fd , std::string& buffer ,const std::string& delimiter);
};

}
