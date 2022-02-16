#define _DEFAULT_SOURCE
/* print files in current directory in reverse order */
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
    struct dirent **namelist;
    int n;

    n = scandir("/proc/", &namelist, 0, alphasort);
    if (n < 0)
        perror("scandir");
    else {
        while (n--) {
            printf("%s ", namelist[n]->d_name);
            free(namelist[n]);
        }
        free(namelist);
    }
}
