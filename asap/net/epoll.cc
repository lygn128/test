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
#include <iomanip>

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
    int ret;
    ee.data.fd = fd;
    ee.events = (EPOLLIN|EPOLLOUT|EPOLLERR|EPOLLET);
    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ee);
    if(ret < 0) {
        std::cout << __LINE__  << " " << __func__ << " " << strerror(errno) << std::endl;
    }
    return ret; 
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
    struct epoll_event * events = (struct epoll_event*)calloc(1000, sizeof(*events));
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
        int nums = epoll_pwait(efd, events, max_events, -1, NULL);
        std::cout << "ret:" << nums << " " << std::strerror(errno) <<  std::endl;
        if(nums < 0) {
            continue;
        }
        int cfd;
        for(int i = 0; i < nums; i++) {
            if( events[i].events  == EPOLLOUT) {
                std::cout << events[i].data.fd << " is ready for write" << std::endl;
                continue;
            }
            if( (events[i].events & EPOLLERR) || (events[i].events & EPOLLHUP) || !(events[i].events & EPOLLIN)) {
                std::cout << __LINE__ << " " << __func__ <<  " " << hex << events[i].events << std::endl;
                close(events[i].data.fd);
                continue;
            }
            if(lfd == events[i].data.fd) {
                struct sockaddr addr;
                int ret;
                socklen_t len = sizeof(addr);
                cfd = accept(lfd, &addr, &len);
                if(cfd > 0) {
                    std::cout << " accept a connect from and cfd = " << cfd  << std::endl;
                    // ret = set_noblock(cfd);
                    // std::cout << "set noblock:" << ret << std::endl;
                    epoll_add(efd, cfd);
                    //std::cout << " epoll add ret:" << ret << std::endl; 
                }
            }else {
                int fd = events[i].data.fd;
                uint32_t flag = events[i].events;
                if(flag & EPOLLIN) {
                    std::cout  << fd  << " ready for " << events[i].events << std::endl;
                    char buff[256];
                    size_t writed =  write(fd, buff, 256);
                    std::cout << "writed:" << writed << std::endl;

                }
                
            }
        }
        //break;
    }
}