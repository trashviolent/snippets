#include <iostream>
#include <fstream>
#include <cstddef>

/*ie. for reading in line of text to be used,
identifiers for object(?), should eliminate any need for text files, 
don't use for console input, used within limits of scene memory,
would only ever be needed for a single line
no need for any destructor*/
class String {
    private:
        uint8_t* str; //null terminated
    public:
        void getLine(std::ifstream &readFile, size_t &filePosition, uint8_t* &memoryPosition);
        void printLine(); //for testing
};

void String::getLine(std::ifstream &readFile, size_t &filePosition, uint8_t* &memoryPosition) {
    //readFile is already at the correct filePosition
    str = memoryPosition;
    int size;
    char input = '-';
    for(size = 0; input != '\0'; ++size) {
        readFile.seekg(filePosition + size);
        readFile.read(&input, 1);
    }
    ++size;
    readFile.seekg(filePosition);
    readFile.read((char*)str, size);
    memoryPosition += size; //increment for the next object to use the block
}

void String::printLine() {
    std::cout << str << std::endl; //this
}

int main() {
    std::ofstream writeFile;
    writeFile.open("test.test", std::ios::binary);
    uint8_t* test = new uint8_t[5];
    test[0] = 116; test[1] = 104; test[2] = 105; test[3] = 115; test[4] = 0;
    writeFile.write((const char*)test, 5);
    writeFile.close();
    writeFile.clear();
    delete[] test;
    uint8_t* test2 = new uint8_t [20];
    uint8_t* pointer = test2 + 5;
    size_t start = 0;
    std::ifstream readFile;
    readFile.open("test.test", std::ios::binary);
    String string;
    string.getLine(readFile, start, pointer);
    readFile.close();
    string.printLine();
    for(int a = 5; a < 9; ++a) {
        std::cout << test2[a]; //this
    }
    std::cout << std::endl;
    delete[] test;
    return 0;
}

/*ie. file contents: this\0
filePosition = 0
input = t
size = 0
input = h
size = 1
input = i
size = 2
input = s
size = 3
input = \0
size = 4*/
