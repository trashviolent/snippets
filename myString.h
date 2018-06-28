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
        uint8_t getSize(); //includes null byte, ie. size of str in bytes, not total space that the string takes up, that is maxSize
        int getLength(); //does not include null byte, ie. length of text
        inline uint8_t getMaxSize() { return maxSize; }
        bool operator==(String &string);
        bool operator==(const char* string);
        void operator=(String &string); //assumes this string's max size can accomodate the copy
        void operator=(const char* string);
        void operator+=(String &string);
        void operator+=(const char* string);
        void clear();
        inline uint8_t getElement(int index) { return str[index]; }
        inline void putElement(int index, uint8_t element) { str[index] = element; }
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

uint8_t String::getSize() { //includes null byte
    uint8_t value;
    for(value = 0; str[value] != 0; ++value) {}
    return value + 1;
}

int String::getLength() {
    int value;
    for(value = 0; str[value] != 0; ++value) {}
    return value;
}

bool String::operator==(String &string) {
    if(string.getSize() != this->getSize())
        return false;
    for(int a = 0; a < this->getLength(); ++a) {
        if(this->str[a] != string.getElement(a))
            return false;
    }
    return true;
}

bool String::operator==(const char* string) {
    int size;
    for(size = 0; string[size] != '\0'; ++size) {}
    if(getSize() != size)
        return false;
    for(int a = 0; a < this->getLength(); ++a) {
        if(str[a] != string[a])
            return false;
    }
    return true;
}

void String::operator=(String &string) {
    for(int a = 0; a < string.getSize(); ++a) {
        this->str[a] = string.getElement(a);
    }
}

void String::operator=(const char* string) {
    int a;
    for(a = 0; string[a] != '\0'; ++a) {
        str[a] = string[a];
    }
    str[a] = '\0';
}

void String::operator+=(String &string) {
    int size = this->getLength();
    for(int a = size; a < (size + string.getLength()); ++a) {
        this->str[a] = string.getElement(a - size);
    }
    this->str[this->getLength()] = '\0';
}

void String::operator+=(const char* string) {
    int size = getLength();
    int size2;
    for(size2 = 0; string[size2] != '\0'; ++size2) {}
    for(int a = size; a < (size + size2); ++a) {
        str[a] = string[a - size];
    }
    str[this->getLength()] = '\0';
}

void String::clear() {
    for(int a = 0; a < maxSize; ++a) {
        str[a] = '\0';
    }
}

void String::printLine() {
    std::cout << str << std::endl; //this
}

int main() {
    std::ofstream writeFile;
    writeFile.open("test.test", std::ios::binary);
    uint8_t* test = new uint8_t[6];
    test[0] = 6; test[1] = 116; test[2] = 104; test[3] = 105; 
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
    start = 0;
    readFile.clear();
    readFile.seekg(start);
    std::cout << readFile.tellg() << std::endl;
    String string2;
    string2.setupLine(readFile, start, pointer);
    readFile.close();
    string.printLine();
    for(int a = 5; a < 9; ++a) {
        std::cout << test2[a]; //this
    }
    std::cout << std::endl;
    std::cout << "size of string: " << (int)string.getSize() << std::endl;
    std::cout << "length of string: " << string.getLength() << std::endl;
    if(string == string2)
        std::cout << "strings are equal" << std::endl; //this runs
    else
        std::cout << "strings are not equal" << std::endl;
    string2.putElement(0, 12);
    if(string == string2)
        std::cout << "strings are equal" << std::endl;
    else
        std::cout << "strings are not equal" << std::endl; //this runs
    string2 = string;
    if(string == string2)
        std::cout << "strings are equal" << std::endl; //this runs
    else
        std::cout << "strings are not equal" << std::endl;
    for(int a = 0; a < string.getLength(); ++a) {
        std::cout << string.getElement(a) << std::endl; //prints this
    }
    for(int a = 0; a < string2.getLength(); ++a) {
        std::cout << string2.getElement(a) << std::endl; //prints this
    }
    std::cout << "final test: ";
    for(int a = 5; a < (string.getLength() + 5); ++a) {
        std::cout << test2[a]; //this
    }
    std::cout << std::endl;
    for(int a = string.getMaxSize() + 5; a < string2.getLength() + string.getMaxSize() + 5; ++a) {
        std::cout << test2[a]; //this
    }
    std::cout << std::endl; //works perfectly
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
