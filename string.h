#include <iostream>
#include <fstream>
#include <cstddef>

class String {
    private:
        char* str; //null terminated
    public:
        void getLine();
        void getLine(std::ifstream &readFile);
};

void String::getLine() {
    
}
