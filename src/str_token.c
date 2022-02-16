#include <stdio.h>  
#include <stdlib.h>
#include <string.h> 
//#include <stdlib.h>

int main (void)
{    
   char cmd[25];
    FILE *fd;   
   int pid = 1414; 
    sprintf(cmd, "ps -o %%p --ppid %d", pid);
   char str[250] = "1417 1428 2401 ";
   char sep[10]= " ";
   printf ("%s\n", str);
   char* istr = strtok (str,sep);

   while (istr != NULL)
   {
      printf("%s\n", istr);
      istr = strtok (NULL,sep);
   }

   exit(EXIT_SUCCESS);
}
