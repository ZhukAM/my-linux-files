#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>

struct sockaddr_in local;
void server (){
    int ss = socket(AF_INET, SOCK_STREAM, 0);
    int cs;

    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(1234);
    local.sin_family = AF_INET;

    bind(ss, (struct sockaddr*) &local, sizeof(local));
    listen(ss, 5);
    cs = accept(ss, NULL, NULL);

    char buf[BUFSIZ];
    read(cs, buf, BUFSIZ);
    printf("%s, bye!\n", buf);
    close(cs);
}

void client(){
    int s = socket(AF_INET, SOCK_STREAM, 0);
    inet_aton("127.0.0.1", &local.sin_addr);
    local.sin_port = htons(1234);
    local.sin_family = AF_INET;
    
    connect(s, (struct sockaddr*) &local, sizeof(local));
    
    char buf[BUFSIZ] = "Hello";
    write(s, buf, strlen(buf) + 1);
    close(s);
}

int main (int c, char** v){
    if(c != 2)
        return 1;
    if(v[1][0] == 's')
        server();
    if(v[1][0] == 'c')
        client();
    return 0;
}
