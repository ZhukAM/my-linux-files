#include <sys/types.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>

void my_signalhandler(int signalno){
    exit(EXIT_FAILURE);
}

int main(){
    pid_t pid;
    pid = fork ();
    if (pid == -1)
        return -1;
    else if (pid != 0){
        //printf("%d %d\n", getpid(), getppid());
        exit (EXIT_SUCCESS);
    }    
    if (setsid () == -1)
        return -1;
    if (chdir ("/") == -1)
        return -1;
    printf("%d\n", getpid()); //getppid());
    signal(SIGURG, my_signalhandler);
    open ("/dev/null", O_RDWR); /* stdin */
    dup (0);                    /* stdout */
    dup (0);                    /* stderror */
    usleep(5000000);
    return 0;
}
