/* chmod_llvm.c - LLVM-compatible version for Assignment 3 */
/* Based on Unix V6 chmod command */

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char **argv) {
    int i;
    int m;
    char c;
    int count;

    if(argc < 3) {
        printf("arg count");
        exit(1);
    }
    
    c = argv[1][0];
    m = 0;
    
    while(c != 0) {
        if(c < 48 || c > 55) {
            printf("bad mode");
            exit(1);
        }
        m = m * 8 + (c - 48);
        c = 1;
    }
    
    count = 0;
    for(i = 2; i < argc; i = i + 1) {
        if(chmod(argv[i], m) < 0) {
            count = count + 1;
            perror(argv[i]);
        }
    }
    
    exit(count);
}
