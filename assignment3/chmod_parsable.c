/* chmod_parsable.c - Fully parsable version for Assignment 3 */
/* Based on Unix V6 chmod command */

int main(int argc, char argv) {
    int i;
    int m;
    char c;
    int count;

    if(argc < 3) {
        printf("arg count");
        exit(1);
    }
    
    c = argv;
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
        if(chmod(argv, m) < 0) {
            count = count + 1;
            perror(argv);
        }
    }
    
    exit(count);
}
