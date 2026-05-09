/* Simple test file for parser verification */

int main() {
    int a;
    int b;
    int c;
    
    a = 5;
    b = 10;
    
    if(a < b) {
        c = a + b;
    } else {
        c = a - b;
    }
    
    while(c < 100) {
        c = c + 1;
    }
    
    return c;
}
