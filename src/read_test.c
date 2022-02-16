#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#define MAX_READ 20
  
int main(void) {
    int rc;
    printf("%d\n", EOF);
    char buffer[MAX_READ], buf[64];
    int numRead = read(0, buffer, MAX_READ);
    if (numRead == -1)
        exit(-1);
    buffer[numRead] = '\0';
    printf("The input data was: %s\n", buffer);
    int fd = open("text.txt", O_RDONLY);
    while(1){
        rc = read(fd, buf, 53);
        buf[rc] = '\0';
        printf("%s", buf);
        if(rc == 0)
            break;          
    }
    return 0;
}
