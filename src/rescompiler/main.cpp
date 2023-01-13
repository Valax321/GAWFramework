extern "C"
{
    #include "filesystem/file_container.h"
}

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

bool readFiles(const char* inputTextFile, std::vector<std::string>& outFiles)
{
    std::ifstream inFile(inputTextFile);
    if (!inFile.is_open())
    {
        printf("Failed to open input file\n");
        return false;
    }

    std::string line;
    while (std::getline(inFile, line))
    {
        outFiles.push_back(line);
    }

    return true;
}

void processFile(const std::string filePath)
{

}

int main(int argc, char* argv[])
{
    // arg1: path to text file with list of files to compile
    // arg2: path to output container

    if (argc < 3)
        return -1;

    const char* inputTextFile = argv[1];
    const char* outputContainer = argv[2];

    printf("Writing to %s\n", outputContainer);

    std::vector<std::string> files{};
    if (!readFiles(inputTextFile, files))
        return -2;
        
    printf("Got %zu files from input\n", files.size());
    for (auto file : files)
    {
        printf("Processing %s\n", file.c_str());
    }

    return 0;
}