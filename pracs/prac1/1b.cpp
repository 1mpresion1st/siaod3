#include <stdio.h>

int main() {
    unsigned char x = 0;  // Начальное значение x
    unsigned char maska = 1;  // 1=00000001 – 8-разрядная маска
    x = x | (maska << 7);  // Установка 7-го бита в 1

    printf("x = %d\n", x);

    return 0;
}
