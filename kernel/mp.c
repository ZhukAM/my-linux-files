/**
* syscall module
* This is the starting point of the kernel module's code execution.
* Right now we will just print a hello and return from here.
*/
  
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <linux/kdev_t.h>
#include <sys/syscall.h>

int write_call( int fd, const char* str, int len) {
    long __res;
    __asm__ volatile ( "int $0x80":
    "=a" (__res):"0"(__NR_write),"b"((long)(fd)),"c"((long)(str)),"d"((long)(len)) );
    return (int) __res;
}

void do_write( void ) {
    char *str = "эталонная строка для вывода!\n";
    int len = strlen( str ) + 1, n;
    printf( "string for write length = %d\n", len);
    n = write_call( 1, str, len );
    printf( "write return : %d\n", n );
}

int mknod_call( const char *pathname, __mode_t  mode, __dev_t dev){
    long __res;
    __asm__ volatile ( "int $0x80":
    "=a" (__res): "a"(__NR_mknod),"b"((long)(pathname)),"c"((long)(mode)),  "d"((long)(dev))
);
    return (int) __res;
};

void do_mknod( void ) {
    char *nam = "ZZZ";
    int n = mknod_call( nam, __S_IFCHR | S_IRUSR | S_IWUSR, MKDEV( 247, 0 ) );
    printf( "mknod return : %d\n", n );
}

int getpid_call( void ) {
    long __res;
    __asm__ volatile ( "int $0x80":"=a" (__res):"a"(__NR_getpid) );
    return (int) __res;
};

void do_getpid( void ) {
    int n = getpid_call();
    printf( "getpid return : %d\n", n );
}

int main() {
    do_getpid();
    do_write();
    do_mknod();
    return EXIT_SUCCESS;
}
