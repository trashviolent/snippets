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
        uint8_t maxSize; //the biggest str can be in memory, ie. the space set aside for it
    public:
        void setupLine(std::ifstream &readFile, size_t &filePosition, uint8_t* &memoryPosition);
        int getSize(); //includes null byte, ie. size of str in bytes
        int getLength(); //does not include null byte, ie. length of text
        void printLine(); //for testing
};

void String::setupLine(std::ifstream &readFile, size_t &filePosition, uint8_t* &memoryPosition) {
    //readFile is already at the correct filePosition
    readFile.read(reinterpret_cast<char*>(&maxSize), sizeof(uint8_t));
    filePosition += 1;
    str = memoryPosition;
    int size;
    char input = '-';
    for(size = 0; input != '\0'; ++size) {
        readFile.read(&input, 1);
    }
    ++size;
    readFile.seekg(filePosition);
    readFile.read((char*)str, size);
    filePosition = readFile.tellg();
    memoryPosition += maxSize; //increment for the next object to use the block
}

int String::getSize() { //includes null byte
    int value;
    for(value = 0; str[value] != 0; ++value) {}
    return value + 1;
}

int String::getLength() {
    int value;
    for(value = 0; str[value] != 0; ++value) {}
    return value;
}

void String::printLine() {
    std::cout << str << std::endl; //this
}

int main() {
    std::ofstream writeFile;
    writeFile.open("test.test", std::ios::binary);
    uint8_t* test = new uint8_t[6];
    test[0] = 10; test[1] = 116; test[2] = 104; test[3] = 105; 
    test[4] = 115; test[5] = 0;
    writeFile.write((const char*)test, 6);
    writeFile.close();
    writeFile.clear();
    delete[] test;
    uint8_t* test2 = new uint8_t [20];
    uint8_t* pointer = test2 + 5;
    size_t start = 0;
    std::ifstream readFile;
    readFile.open("test.test", std::ios::binary);
    String string;
    string.setupLine(readFile, start, pointer);
    readFile.close();
    string.printLine();
    for(int a = 5; a < 9; ++a) {
        std::cout << test2[a]; //this
    }
    std::cout << std::endl;
    std::cout << "size of string: " << string.getSize() << std::endl;
    std::cout << "length of string: " << string.getLength() << std::endl;
    delete[] test;
    return 0;
}

/*ie. file contents: this\0
filePosition = 1
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
