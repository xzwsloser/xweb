#include "SocketUtils.h"
#include "../logger/Logger.h"
#include <asm-generic/socket.h>
#include <sys/signal.h>
#include<cstring>
#include<unistd.h>
#include<fcntl.h>
#include<sys/socket.h>
#include<arpa/inet.h>

namespace xweb {

void SocketUtils::ignoreSigPipe()
{
    struct sigaction sa;
    memset(&sa , 0 , sizeof(sa));
    sa.sa_handler = SIG_IGN;
    sa.sa_flags = 0;
    if(sigaction(SIGPIPE , &sa , nullptr)) return;
}

int SocketUtils::setSocketNoBlocking(int fd)
{
    int flag = fcntl(fd , F_GETFL , 0);
    if(flag == -1) return -1;
    flag |= O_NONBLOCK;
    if(fcntl(fd, F_SETFL , flag) == -1) return -1;
    return 0;
}

int SocketUtils::socketBindListen(int port)
{
    if(port < 0 || port > 65535)
    {
        LOG_ERROR << "port is not in range";
        return -1;
    }
    
    int listenfd;
    if((listenfd = socket(AF_INET , SOCK_STREAM , 0)) == -1) return -1;
    
    int optval = 1;
    if(setsockopt(listenfd, SOL_SOCKET , SO_REUSEADDR , &optval, sizeof(optval)) == -1) {
        close(listenfd);
        return -1;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons((uint16_t)port);
    
    if(bind(listenfd , (struct sockaddr*)&server_addr , sizeof(server_addr)) < 0) {
        close(listenfd);
        return -1;
    }

    if(listen(listenfd , 2048) == -1) {
        close(listenfd);
        return -1;
    }

    if(listenfd == -1) {
        close(listenfd);
        return -1;
    }
    return listenfd;
}

}
