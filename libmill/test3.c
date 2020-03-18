#include <stdio.h>
#include "libmill.h"

coroutine void print(char what) {
    msleep(now() + 1000);
    putchar(what);
}

int main(void) {
    setvbuf(stdout, (char*)NULL, _IONBF, 0);
    char ch;
    for (ch='a'; ch<='z'; ch++) {
        go(print(ch));
    }
    return 0;
}
