#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    int fd = open("/proc/self/stat", O_RDONLY);
    char* buf = calloc(100, sizeof(char));
    read(fd, buf, 100);
    int ntoken = 1;
    char* token = strtok(buf, " ");

    while (token) {
	ntoken++;
	token = strtok(NULL, " ");
	if (ntoken == 4) {
	    printf("%s\n", token);
	    break;
	}
    }

    free(buf);
    close(fd);

    return 0;
}
