/* chmod_final.c - Version for Assignment 3 Parser Analysis */
/* Simplified from Unix V6 chmod command */

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
    
    for(m = 0; c != 0; c = 1) {
        if(c < 48 || c > 55) {
            printf("bad mode");
            exit(1);
        }
        m = (m << 3) | (c - 48);
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
