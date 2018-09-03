#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <vector>

class FileReader
{
public:
    FileReader();

    static std::vector<unsigned char> ReadAllBytes(std::string filename);
};

#endif // FILEREADER_H
