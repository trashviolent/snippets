#include <iostream>
#include <cstddef>

void testFunc(uint8_t* &address) {
    std::cout << &address << std::endl;
    uint8_t* test = address + 2;
    test[0] = 5;
    test[1] = 7;
}

int main() {
    uint8_t* test = new uint8_t[10];
    test[0] = 1;
    test[1] = 2;
    testFunc(test);
    for(int a = 0; a < 4; ++a) {
        std::cout << (int)test[a] << std::endl;
    }
    delete[] test;
    return 0;
}
