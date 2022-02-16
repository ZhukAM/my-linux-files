#define _GNU_SOURCE
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>

extern int opterr;

int main(int argc, char** argv){
    int c = 0; char result = '+';
    int query = 0;
    int option_index = 0;
        
    static struct option long_options[] = {
        {"query", required_argument, 0, 'q'},
        {"longinformationrequest", no_argument, 0, 'i'},
        {"version", no_argument, 0, 'v'}, 
        {0, 0, 0, 0}
    };
    opterr = 0;
    while( (c = getopt_long (argc, argv, "+q:ilv",
                 long_options, &option_index)) != -1){
         
        switch(c){
            case 'q':
                if(atoi(optarg) == 0) result = '-';
                //printf("optarg=%d\n", query); 
                break;
            case 'i':
                //result = '+';
                break;    
            case 'l':    
                //result = '+';
                //printf("long information request\n");
                break;
            case 'v':
                result = '+';    
                //printf("llvm-10\n");
                break;
            default:
                result = '-';
                break;
        } 

    }
    
    printf("%c\n", result);
    return 0;
}
