#include <stdio.h>
#include "libmill.h"

coroutine void sender(chan channel) {
    msleep(now() + 1000);
    chs(channel, int, '*');
    chclose(channel);
}

int main() {
    setvbuf(stdout, (char*)NULL, _IONBF, 0);
    chan channel = chmake(int, 0);
    puts("vytvoreni korutiny");
    go(sender(chdup(channel)));
    puts("cekani na zpravu z korutiny");
    char c = chr(channel, int);
    puts("prijato");
    putchar(c);
    chclose(channel);
    return 0;
}
