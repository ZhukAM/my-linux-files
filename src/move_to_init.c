#include <stdio.h>
#include <stdlib.h>
#include <string.h>
   
void path(char* s1, char* s2);
   
int main(int argc, char * argv[]){
    char* pid = argv[1];
    while (1){
        char pref[30] = "/proc/";
        path(pref, pid);
        FILE* file;
        if ((file = fopen(pref, "r")) != NULL){
            int ppid; 
            fscanf(file, "%*d %*s %*c %d", &ppid);
            sprintf(pid,"%d", ppid);
            fclose (file);
            if (ppid == 1) {
                printf("%d\n", ppid);
                return 0;
            }
        } else break;
       }    
      return 0;
  }
 
 void path(char* s1, char* s2){
      printf("%s\n", s2);
      strcat(s1, s2);
      strcat(s1, "/stat");
  }

