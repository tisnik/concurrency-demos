#include <stdio.h>
#include "libmill.h"

coroutine void print(char what) {
    putchar(what);
}

int main(void) {
    char ch;
    for (ch='a'; ch<='z'; ch++) {
        go(print(ch));
    }
    return 0;
}
