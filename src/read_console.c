#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main(int arc, char* argv[]){
    char path[50]= {0};
    int count = 0;
    sprintf(path, "%s %s", argv[1], argv[2]);    
    FILE* file = popen(path, "r");
    int c;
    while((c = fgetc(file)) != EOF){
        if(c == '0') count++;    
    }    
    printf("%d", count);
    pclose(file);
    return 0;
}

