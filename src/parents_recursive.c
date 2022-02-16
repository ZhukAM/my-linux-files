#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void show_parrents_PID(int pid)
{
	printf("%d\n", pid);
	if (pid == 1)
		return;
  	char path[50];
	sprintf(path, "/proc/%d/stat", pid);	
		
       	FILE* file = fopen(path, "r");
        if (file == NULL) {
       	        printf("Cannot open file %s\n", path);
               	exit(1);
        } else {
       	        fscanf(file, "%*d %*s %*c %d", &pid);
		fclose(file);
	}
	show_parrents_PID(pid);	
}

int main(int argc, char* argv[])
{
	int pid = -1;
	if (argc != 2)
		printf("To few arguments.\n");
	else {
		pid = atoi(argv[1]);
		show_parrents_PID(pid);
	}   
    return 0;
}    
