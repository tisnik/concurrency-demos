#include <stdio.h>
#include "libmill.h"

coroutine void sender1(chan channel) {
    int i;
    for (i=0; i<10; i++) {
        msleep(now() + 1000);
        chs(channel, int, '*');
    }
    chclose(channel);
}

coroutine void sender2(chan channel) {
    int i;
    for (i=0; i<10; i++) {
        msleep(now() + 800);
        chs(channel, int, '?');
    }
    chclose(channel);
}

int main() {
    chan channel1 = chmake(int, 0);
    chan channel2 = chmake(int, 0);

    puts("vytvoreni korutin");
    go(sender1(chdup(channel1)));
    go(sender2(chdup(channel2)));

    setvbuf(stdout, (char*)NULL, _IONBF, 0);

    puts("cekani na zpravy z korutin");
    int i;
    for (i=0; i<100; i++) {
        choose {
            in(channel1, int, val):
                putchar(val);
            in(channel2, int, val):
                putchar(val);
            otherwise:
                putchar('-');
            end
        }
        msleep(now() + 50);
    }
    chclose(channel1);
    chclose(channel2);
    return 0;
}
