#include <stdio.h>
#include <string.h>

int system(char* s);
int main(int argc, char * argv[]){
    system("cat /proc/[0-9]*/comm | grep genenv |wc -l");
	return 0;
}

