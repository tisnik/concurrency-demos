#include <stdio.h>
#include "libmill.h"

coroutine void foo() {
    puts("foo");
}

coroutine void bar() {
    puts("bar");
}

int main(void) {
    go(foo());
    go(bar());
    return 0;
}
