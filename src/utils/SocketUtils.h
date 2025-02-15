// @Author: loser
#pragma once

namespace xweb {

class SocketUtils {
public:
    SocketUtils() = delete;
    ~SocketUtils() = delete;
    
    static void ignoreSigPipe();
    static int setSocketNoBlocking(int fd);
    static int socketBindListen(int port);
};

}
