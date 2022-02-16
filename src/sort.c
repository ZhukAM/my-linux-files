#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000

 int cmp(const void *a, const void *b) {
     return *(char*)b - *(char*)a;
 }
 int main() {
    const char* text = "OFF";
    int i, n;
    char* arr = (char*) calloc(5000, sizeof(char));
    while(1){
        fgets(arr, 100, stdin);
        if(strncmp(arr, text, 3) == 0) break;
        for(i = 0 ; arr[i] != 0; i++) { 
            printf("%c", arr[i]);
            n = i;
        }
        printf("\n");
        qsort(arr, n, sizeof(char), cmp );
        for(i = 0 ; arr[i] != 0; i++) { 
            printf("%c", arr[i]);
        }
    }   
    free(arr);
    return 0;
 }
