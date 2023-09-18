#include <stdio.h>

int main() {
    unsigned char x = 255;  // 8-разрядное двоичное число 11111111
    unsigned char maska = 1;  // 1=00000001 – 8-разрядная маска
    x = x & (~(maska << 4));  // результат x=239

    printf("x = %d\n", x);

    return 0;
}
