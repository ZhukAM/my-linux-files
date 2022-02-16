#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <fcntl.h> 
#define BUFFER_SIZE 64

int main(int argc, char* argv[]){
    int fds[2]; int rc, count = 0; 
    char buf[1024];
    if((fds[0] = open("./in1", O_RDONLY)) < 0)
        return -1;
    if((fds[1] = open("./in2", O_RDONLY)) < 0)
        return -1;
    fd_set watch_set;
    fd_set in_set;
    FD_ZERO(&watch_set);
    FD_SET(fds[0], &watch_set);
    FD_SET(fds[1], &watch_set);
    while(FD_ISSET(fds[0], &watch_set) || FD_ISSET(fds[1], &watch_set)){
        in_set = watch_set;
        if(select(fds[1]+1, &in_set, NULL, NULL, NULL) < 0)
            return 1;
        for(int i = 0; i < 2; ++i){
            if(FD_ISSET(fds[i], &in_set)){
                rc =read(fds[i], buf, BUFFER_SIZE);
                if(rc < 0) return 1;
                if(rc == 0){
                    close(fds[i]);
                    FD_CLR(fds[i], &watch_set); 
                }
                buf[rc] = '\0';      
                printf("%s\n", buf);
                for (int i = 0; buf[i] != '\0'; ++i)
                    count += atoi(buf+i);
            }
        }   
    }
    printf("%d\n", count);
    return 0;
}
