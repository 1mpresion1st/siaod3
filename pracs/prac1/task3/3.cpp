#include <iostream>
#include <fstream>


int main() {
    const int K = 131000;
    unsigned long long bits[K];
    for (unsigned long long & bit : bits) {
        bit = 0;
    }
    std::cout << "Bit array size: " << (double)K*sizeof(unsigned long long)/(1024*1024) << "MiB" << std::endl;

    auto file_in_name = "pracs/prac1/task3/input.txt";
    auto file_out_name = "pracs/prac1/task3/output.txt";

    // read input and fill bitset
    auto fin = std::ifstream(file_in_name);

    if (!fin.is_open()) {
        std::cout << "Can't open file " << file_in_name << std::endl;
        return -1;
    }


    int n;
    while (fin >> n) {
        if (!(n >= 1000000 && n <= 9000000)) {
            std::cout << "Numbers must be in range 1000000..9000000!";
            return -1;
        }
        bits[(n-1000000)/64] |= (1ULL << (n-1000000)%64);
    }

    // write sorted sequence to file
    auto fout = std::ofstream(file_out_name);

    if (!fin.is_open()) {
        std::cout << "Can't open file " << file_out_name << std::endl;
        return -1;
    }

    for (int x=1000000; x <= 9000000; x++) {
        if (bits[(x-1000000)/64] & (1ULL << (x-1000000)%64)) {
            fout << x << std::endl;
        }
    }

    return 0;
}
