#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/fs.h>


int main(){
    pid_t pid;
    pid = fork ();
    if (pid == -1)
        return -1;
    else if (pid != 0){
        printf("%d %d\n", getpid(), getppid());
        exit (EXIT_SUCCESS);
    }    
    if (setsid () == -1)
        return -1;
    if (chdir ("/") == -1)
        return -1;
    printf("%d %d\n", getpid(), getppid());
    open ("/dev/null", O_RDWR); /* stdin */
    dup (0); /* stdout */
    dup (0); /* stderror */
    pause();
    return 0;
}
