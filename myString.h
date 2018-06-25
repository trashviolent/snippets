#include <iostream>
#include <fstream>
#include <cstddef>

/*ie. for reading in line of text to be used,
identifiers for object(?), should eliminate any need for text files, 
don't use for console input, used within limits of scene memory,
would only ever be needed for a single line*/
class String {
    private:
        uint8_t* str; //null terminated
    public:
        void getLine(std::ifstream &readFile, size_t &filePosition, uint8_t* &memoryPosition);
};

int main() {
    String string;
    string.getLine();
    return 0;
}
