#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

int open_serverfd(char *port)
{
    int listenfd = -1, optval = 1;
    struct addrinfo hints, *listp, *p;
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;
    getaddrinfo(NULL, port, &hints, &listp);

    for (p = listp; p; p = p->ai_next)
    {
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0)
        {
            continue;
        }
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, (const void *)&optval, sizeof(int));
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0)
        {
            printf("bind success\n");
            int ret = listen(listenfd, 512);
            printf("listen ret: %d\n", ret);
            break;
        }
        close(listenfd);
    }

    freeaddrinfo(listp);
    if (!p)
        return -1;
    return listenfd;
}

int main()
{
    int srv_fd;
    int client_fd;
    srv_fd = open_serverfd("1080");
    printf("srv_fd is %d\n", srv_fd);

    while (1)
    {
        struct sockaddr client_con;
        socklen_t len;
        client_fd = accept(srv_fd, &client_con, &len);
        if (client_fd == -1)
        {
            printf("accept err %d\n", client_fd);
            continue;
        }
        if (fork() == 0)
        {
            close(srv_fd);
            return 0;
        }
        close(client_fd);
    }
}