#include <stdio.h>
#include "libmill.h"

coroutine void foo() {
    puts("foo");
}

coroutine void bar() {
    puts("bar");
}

int main(void) {
    setvbuf(stdout, (char*)NULL, _IONBF, 0);
    go(foo());
    go(bar());
    return 0;
}
