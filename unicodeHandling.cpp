/*to change exe name, 
Open project properties, general, target name*/

#include <windows.h>
#include <fstream>
#include <filesystem>
#include <iostream>

std::string getProgramName(bool getExtension) {
	std::string programName = u8"testingName天下1";
	if (getExtension) {
		//if os == windows
		programName += ".exe";
	}
	return programName;
}

std::filesystem::path getUnicodePath(std::string programName, std::string fileName) {
	std::string programPath;
	//preprocessor if os == windows start
	wchar_t* windowsProgramPath;
	windowsProgramPath = new wchar_t[MAX_PATH];
	GetModuleFileNameW(NULL, windowsProgramPath, MAX_PATH);
	std::wstring windowsWStringPath(windowsProgramPath);
	int programPathSize = WideCharToMultiByte(CP_UTF8, 0, &windowsWStringPath[0], -1, NULL, 0, NULL, NULL);
	programPath = std::string(programPathSize, 0);
	WideCharToMultiByte(CP_UTF8, 0, &windowsWStringPath[0], (int)windowsWStringPath.size(), &programPath[0], programPathSize, NULL, NULL);
	delete[] windowsProgramPath;
	programPath.pop_back(); //removes null byte
	//preprocessor if os == windows end
	//else get programPath another way
	int directoryPathLength = programPath.length() - programName.length();
	std::string filePath;
	for (int a = 0; a < directoryPathLength; ++a) {
		filePath += programPath[a];
	}
	for (int a = 0; a < fileName.length(); ++a) {
		filePath += fileName[a];
	}
	std::filesystem::path portableUnicodePath = filePath;
	return portableUnicodePath;
}

int main() {
	std::string fileName = u8"testFile.txt";
	std::string writeToFile = u8"testdir天下ex";
	std::ofstream writeFile(getUnicodePath(getProgramName(true), fileName), std::ios::binary);
	writeFile.write(writeToFile.c_str(), writeToFile.size());
	writeFile.close();
	writeFile.clear();
	std::cout << "writeToFile: " << writeToFile << std::endl;
	std::ifstream readFile(getUnicodePath(getProgramName(true), fileName), std::ios::binary);
	char* fileRead = new char[writeToFile.length() + 1];
	readFile.read(fileRead, writeToFile.length());
	readFile.close();
	fileRead[writeToFile.length()] = u8'\0';
	writeToFile = fileRead;
	std::cout << "writeToFile: " << writeToFile << std::endl;
	delete[] fileRead;
	writeFile.open(getUnicodePath(getProgramName(true), fileName), std::ios::binary);
	writeFile.write(writeToFile.c_str(), writeToFile.size());
	writeFile.close();
	writeFile.clear();
	return 0;
}