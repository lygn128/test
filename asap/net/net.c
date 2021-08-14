#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

int open_clientfd2(char *hostname, char *port)
{
    struct hostent *hosts = gethostbyname(hostname);
    printf(" length is %d  %s\n", hosts->h_length, hosts->h_name);
    char **pptr;
    for (pptr = hosts->h_aliases; *pptr != NULL; pptr++)
    {
        printf("alias %s\n", *pptr);
    }
    char buff[256];
    switch (hosts->h_addrtype)
    {
    case AF_INET:
        pptr = hosts->h_addr_list;
        for (; *pptr != NULL; pptr++)
        {
            inet_ntop(hosts->h_addrtype, *pptr, buff, sizeof(buff));
            printf("addr is %s\n", buff);
        }
        break;

    default:
        break;
    }
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

int open_clientfd(char *hostname, char *port)
{
    int clientfd;
    struct addrinfo hints, *listp, *p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;
    hints.ai_flags |= AI_ADDRCONFIG;
    getaddrinfo(hostname, port, &hints, &listp);
    for (p = listp; p; p = p->ai_next)
    {
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
        {
            continue;
        }

        if (connect(clientfd, p->ai_addr, p->ai_addrlen) != -1)
            break;
        close(clientfd);
    }
    freeaddrinfo(listp);
    printf("clinet fd is %d\n", clientfd);
    if (!p)
        return -1;
    else
        return clientfd;
}

// int testpoint()
// {
//     int arry[10];
//     int *a = &arry;
//     printf("%p  %p\n", a, a + 1);
//     printf("%p  %p\n", &a, &a + 1);
// }

int main(int argc, char **argv)
{
    int x = open_serverfd("2080");
    printf("x is: %d\n", x);
    int connfd;
    
    while(1) {
        struct sockaddr_in clientaddr;
        socklen_t clientlen = sizeof(clientaddr);
        connfd = accept(x, (struct sockaddr*)&clientaddr, &clientlen);
        if(connfd == -1 ) {
            printf("accepted %d\n", connfd);
            break;
        }
        char buff[INET_ADDRSTRLEN+1];
        const char * ip = inet_ntop(AF_INET, &clientaddr.sin_addr, buff, INET_ADDRSTRLEN);
        printf("accept a conn and ip is %s   and port is %d\n", buff, ntohs(clientaddr.sin_port));
    }
    printf("%d\n", x);
    sleep(100);
    struct addrinfo *p, *listp, hints;
    struct sockaddr_in *sockp;
    char buff[256];
    int rc, flags;
    if (argc != 2)
    {
        fprintf(stderr, "use :%s <domain name>\n", argv[0]);
        exit(0);
    }
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    if ((rc = getaddrinfo(argv[1], NULL, &hints, &listp)) != 0)
    {
        fprintf(stderr, "getaddrinfo err : %s\n", gai_strerror(rc));
    }

    // flags = NI_NUMERICHOST;
    // for (p = listp; p; p = p->ai_next) {
    //     getnameinfo(p->ai_addr, p->ai_addrlen, buff, 256, NULL, 0, flags);
    //     printf("%s\n", buff);
    // }

    // freeaddrinfo(listp);

    for (p = listp; p; p = p->ai_next)
    {
        sockp = (struct sockaddr_in *)p->ai_addr;
        const char *str = inet_ntop(AF_INET, &(sockp->sin_addr), buff, 256);
        printf("%s ", buff);
    }

    open_clientfd(argv[1], "80");

    exit(0);
}