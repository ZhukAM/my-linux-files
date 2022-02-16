#include <inttypes.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <malloc.h>

int main(int argc, char * argv[]){
    char* ps = argv[1];
    char sep[] = " "; const char pref[] = "/proc/";
    char middle[] = "/task/", path[50] = "%s%d%s%d%s";
    char tail[] = "/children"; int count = 0; 
    while (ps[0] != 0 ) {
        printf("%s\n", ps);
        char ps1[1000] = {'\0'};
        char* istr = strtok(ps, sep);
        while (istr != NULL) {       
            int num = atoi(istr); 
            char ps2[250] = {'\0'};
            sprintf(path,"%s%d%s%d%s", pref, num, middle, num, tail);
            fgets(ps2, sizeof(ps2), fopen(path, "r"));
            strcat(ps1, ps2);            
            istr = strtok(NULL, sep);
        } 
        ps =  ps1;     
    }
}    

