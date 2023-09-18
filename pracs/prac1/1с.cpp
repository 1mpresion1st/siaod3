#include <cstdlib>
#include <iostream>
//#include <Windows.h>
#include <bitset>
using namespace std;

int main() {
//    SetConsoleCP(1251);
//    SetConsoleOutputCP(1251);
    unsigned int x = 25;
    const int n = sizeof(int) * 8; // Количество разрядов в числе типа int (обычно 32)
    unsigned maska = (1 << (n - 1)); // Устанавливаем 1 в старшем бите 32-разрядной сетки

    cout << "Начальный вид маски: " << bitset<n>(maska) << endl;
    cout << "Результат: ";

    for (int i = 1; i <= n; i++) {
        // Проверяем текущий бит числа x с текущей маской и сдвигаем его вправо на правильную позицию
        cout << ((x & maska) >> (n - i));

        maska = maska >> 1; // Сдвигаем 1 в маске на один разряд вправо
    }
    cout << endl;

//    system("pause");
    return 0;
}
