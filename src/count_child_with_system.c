#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    char command_bash[100] = {0};
    sprintf(command_bash, "/home/kali/aleks/bash_children.sh %s", argv[1]);
    system(command_bash);

    int num = atoi(argv[1]);
    char name[] = "pstree -pT";
    char other[] = "|grep -E '[\([:digit:])]{1,}' |wc -w";
    char command[50] = "%s %d %s"; 
    sprintf(command,"%s %d %s", name, num, other);
    system(command);
	return 0;
}

