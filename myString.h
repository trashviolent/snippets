#include <iostream>
#include <fstream>
#include <cstddef>

/*ie. for reading in line of text to be used,
identifiers for object(?), */
class String {
    private:
        char* str; //null terminated
    public:
        void getLine();
        //void getLine(std::ifstream &readFile);
};

void String::getLine() {
    char a;
    std::cin.get(a);
    std::cin.putback(a);
    size_t size = std::cin.rdbuf()->in_avail();
    std::cout << size << std::endl;
    if(size > 0) {
        str = new char[size];
        std::cin.getline(str, size);
        std::cout << str << std::endl;
        delete[] str;
    }
}

int main() {
    String string;
    string.getLine();
    return 0;
}
