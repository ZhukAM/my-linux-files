#define _GNU_SOURCE
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

 int count_USR1 = 0;
 int count_USR2 = 0;

void signalhandler(int signalno){
    if (signalno == SIGUSR1)
        count_USR1++;
    else if (signalno == SIGUSR2)
        count_USR2++;
    else if (signalno == SIGTERM){
        printf("%d %d\n", count_USR1, count_USR2);
        exit(EXIT_SUCCESS);
    }    
    else exit(EXIT_FAILURE);
}

int main(){
    signal(SIGUSR1, signalhandler);
    signal(SIGUSR2, signalhandler);
    signal(SIGTERM, signalhandler);
    while(1)
        pause(); 
    return 0;
}
