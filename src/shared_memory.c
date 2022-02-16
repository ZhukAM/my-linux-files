#define _XOPEN_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(int arc, char* argv[]){
    key_t key1 = atoi(argv[1]); 
    key_t key2 = atoi(argv[2]);
    int shm1 = shmget(key1, 1000*sizeof(char), IPC_CREAT | 0600);
    int shm2 = shmget(key2, 1000*sizeof(char), IPC_CREAT | 0600);
    key_t key_new = ftok("shared_memory.c", 1);
    printf("%d\n", key_new);
    int shm3 = shmget(key_new, 1000*sizeof(char), IPC_CREAT | 0666);    
    int* i1 = (int*)shmat(shm1, NULL, SHM_RDONLY);
    int* i2 = (int*)shmat(shm2, NULL, SHM_RDONLY);
    int* i3 = (int*)shmat((key_t) shm3, NULL, 0);
    for(int count = 0; count < 100 ; ++count, ++i1, ++i2, ++i3){
       *i3 = *i1 + *i2; 
    }
    shmdt(i1); shmdt(i2); shmdt(i3);
    return 0;
}


