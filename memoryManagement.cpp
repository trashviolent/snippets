#include <iostream>

int main() {
    char* memblock = new char[20];
    std::cout << &memblock << std::endl;
    char* test1 = memblock;
    char* test2 = memblock + 10;
    for(int a = 0; a < 10; ++a) {
        test1[a] = 97 + a;
    }
    for(int a = 0; a < 10; ++a) {
        test2[a] = 97 + a;
    }
    for(int a = 0; a < 10; ++a) {
        std::cout << test1[a];
    }
    
    std::cout << std::endl;
    for(int a = 0; a < 10; ++a) {
        std::cout << test2[a];
    }
    std::cout << std::endl;
    for(int a = 0; a < 20; ++a) {
        std::cout << memblock[a];
    }
    std::cout << std::endl;
    //delete[] test1;
    delete[] memblock;
    return 0;
}
