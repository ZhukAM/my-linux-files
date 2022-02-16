#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

struct sockaddr_in local;
//struct in_addr ; 

int main (int c, char** v){
  //const char* src = "127.0.0.1";
    int port = atoi(v[1]);
    int s = socket(AF_INET, SOCK_DGRAM, 0);

    inet_aton("127.0.0.1", &local.sin_addr);
    //inet_pton(AF_INET, );
    local.sin_port = htons(port);
    local.sin_family = AF_INET;

    int result = bind(s, (struct sockaddr*) &local, sizeof(local));
    const char * text = "OFF\n";
    while(1){
        char buf[BUFSIZ];
        int len = read(s, buf, BUFSIZ);
        buf[len] = '\0';
        if(strncmp(buf, text, 4) == 0) break;
        printf("%s\n", buf);
    }
    return 0;
}
