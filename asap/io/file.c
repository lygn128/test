#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>

int main()
{

    int fd1, fd2, fd3;
    fd3 = open("./log", O_CREAT|O_RDWR, 0);
    printf("fd3 is %d\n", fd3);
    
    int ret;
    ret = dup2(fd3, STDOUT_FILENO);
    printf("dump ret: %d\n", ret);
    struct stat buff;
    DIR *dir = NULL;
    struct dirent * dep = NULL;



    fd1 = open("file.c", O_RDONLY, 0);
    close(fd1);
    fd2 = open("a.out", O_RDONLY, 0);
    printf("fd2 = %d\n", fd2);
    ret = stat("file.c", &buff);
    printf("size of %d  %d\n", buff.st_ino, buff.st_size);
    ret = stat("a.out", &buff);
   // printf("size of %d  %d  %d\n", buff.st_ino, buff.st_size, buff.st_mode);

    //open dir 
    dir = opendir("../../");
    if(dir) {
        printf("open dir suc\n");
        while ((dep = readdir(dir)) != NULL) {
            printf("%s %d\n", dep->d_name, dep->d_ino);
        }
    }
    close(fd3);
    exit(0);
}