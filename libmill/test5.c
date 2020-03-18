#include <stdio.h>
#include "libmill.h"

coroutine void print(char what) {
    int i;

    for (i=0; i<10; i++) {
        putchar(what);
        yield();
        msleep(now() + 100);
    }
}

int main(void) {
    char ch;
    for (ch='a'; ch<='z'; ch++) {
        go(print(ch));
    }
    msleep(now() + 200);
    return 0;
}
