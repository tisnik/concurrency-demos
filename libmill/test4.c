#include <stdio.h>
#include "libmill.h"

coroutine void print(char what) {
    int i;

    for (i=0; i<10; i++) {
        msleep(now() + 100);
        putchar(what);
    }
}

int main(void) {
    setvbuf(stdout, (char*)NULL, _IONBF, 0);
    char ch;
    for (ch='a'; ch<='z'; ch++) {
        go(print(ch));
    }
    msleep(now() + 200);
    return 0;
}
