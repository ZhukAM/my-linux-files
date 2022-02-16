#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char * argv[]){
    char arr[50];
    char strPPid[5] = "PPid";
    char sep[5] = "d:";
    FILE *f = fopen("/proc/self/status", "r");
    while (1) {
        fgets(arr, sizeof(arr), f);
        if (strstr(arr, strPPid) != NULL) {
            char *istr = strtok(arr, sep);
            while (istr != NULL) {
                if (atoi(istr) != 0){
                    printf("%d\n", atoi(istr));
                    break;
                }
                istr = strtok(NULL, sep);
            }
            break;
        }
    }
    fclose(f);
    return 0;
}
