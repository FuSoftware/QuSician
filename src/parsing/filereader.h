#ifndef FILEREADER_H
#define FILEREADER_H

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class FileReader
{
public:
    FileReader();

    static std::vector<unsigned char> ReadAllBytes(string filename);
};

#endif // FILEREADER_H
