#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define CHILDS 7
int main(int argc, char **argv) {
    char buf[128];
    int i,j=1;
    printf("%d\n", getpid());
    sprintf(buf, "pstree -p %d", getpid() );
    for(i=0; i!=CHILDS; i++)
    {
        if(fork()==0){
             printf("%d\tI'm child [%d]\n", getpid(), i+1);
             break;
         }
         else  j=0;
         if(j==1){
                     printf("%d\tHello! I'm parent!\n", getpid());
                     system(buf);
    }
    scanf("%d", &i);
}
