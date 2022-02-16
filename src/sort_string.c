#include <stdbool.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netdb.h>


int cmp(const void *a, const void *b) {
    return *(char*)b - *(char*)a;
} 

struct sockaddr_in local;

void server (const char* port){
    int ss = socket(AF_INET, SOCK_STREAM, 0);
    int cs, i, n;
    const char* text = "OFF";

    inet_pton(AF_INET, "127.0.0.1", &local.sin_addr);
    local.sin_port = htons(atoi(port));
    local.sin_family = AF_INET;

    int err = bind(ss, (struct sockaddr*) &local, sizeof(local));
    if(err < 0) 
        exit(1);
    listen(ss, 5);   
    cs = accept(ss, NULL, NULL);

    while(1){
        char* arr = (char*) calloc(100, sizeof(char));
        read(cs, arr, 99);
        if(strncmp(arr, text, 3) == 0) break;
        for(i = 0 ; arr[i] != '\0'; ++i)
            printf("%c", arr[i]);
        printf("\n");
        qsort(arr, strlen(arr), sizeof(char), cmp );
        for(i = 0 ; arr[i] != 0; ++i) {
            printf("%c", arr[i]);
        }
        write(cs, arr, strlen(arr)+1);
        free(arr); 
    }    
    close(cs);
}

void client(const char* port){
    char* arr = (char*) malloc((BUFSIZ+1)*sizeof(char));
    int s = socket(AF_INET, SOCK_STREAM, 0);
    inet_pton(AF_INET, "127.0.0.1", &local.sin_addr);
    local.sin_port = htons(atoi(port));
    local.sin_family = AF_INET;
    
    int err = connect(s, (struct sockaddr*) &local, sizeof(local));
    
    while(true){
        fgets(arr, 100, stdin);
        write(s, arr, strlen(arr)+1);
    } 
    close(s);
    free(arr);
}

int main (int c, char** v){
    if(c != 3)
        return 1;
    if(v[1][0] == 's')
        server(v[2]);
    if(v[1][0] == 'c')
        client(v[2]);
    return 0;
}
