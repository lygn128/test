#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <netdb.h>
#include <string.h>
#include <fcntl.h>
#include <cerrno>
#include <cstring>

int set_noblock(int fd) {
    int flags;
    if((flags = fcntl(fd, F_GETFL,0)) < 0) {
        close(fd);
        return -1;
    }
    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) < 0) {
        close(fd);
        return -1;
    }
    return flags;
}

int epoll_add(int epfd, int fd) {
    struct epoll_event ee;
    ee.data.fd = fd;
    ee.events = (EPOLLIN|EPOLLOUT|EPOLLERR);
    return epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ee);
}
int open_serverfd(char * port) {
    int listenfd = -1, optval = 1;
    struct addrinfo hints, *listp, *p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE|AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;
    getaddrinfo(NULL, port, &hints, &listp);


    for ( p = listp; p; p = p->ai_next) {
        if ( (listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
            continue;
        }
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void*)&optval, sizeof(int));
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0) {
            printf("bind success\n");
            int ret = listen(listenfd, 512);
            printf("listen ret: %d\n", ret);
            break;
        }
        close(listenfd);
    }

    freeaddrinfo(listp);
    if(!p) return -1;
    return listenfd;
}

int main() {
    int ret;
    struct epoll_event * events;
    int max_events = 10000;
    int efd = epoll_create1(EPOLL_CLOEXEC);
    std::cout << "fd is:" << efd << std::endl;
    int lfd = open_serverfd("2048");
    
    if(lfd <  0 ) {
        std::cout << "open fail " << lfd << std::endl;
        return -1;
    }

    ret = epoll_add(efd, lfd);
    std::cout << "add ret is:" << ret << std::endl;
    while(1) {
        int nums = epoll_wait(efd, events, max_events, -1);
        std::cout << "ret:" << nums << " " << std::strerror(errno) <<  std::endl;
        break;
    }
}