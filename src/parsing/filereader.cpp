#include "filereader.h"

FileReader::FileReader()
{

}

std::vector<unsigned char> FileReader::ReadAllBytes(std::string filename)
{
    std::ifstream is (filename, std::ifstream::binary);
    std::vector<unsigned char> result;

    if (is) {
        // get length of file:
        is.seekg (0, is.end);
        int length = is.tellg();
        is.seekg (0, is.beg);

        char *buffer = new char [length];

        //cout << "Reading " << length << " characters... " << endl;
        // read data as a block:
        is.read (buffer,length);

        if (!is)
          std::cout << "error: only " << is.gcount() << " could be read" << std::endl;
        is.close();

        // ...buffer contains the entire file...



        for(int i = 0;i<length;i++)
            result.push_back(buffer[i]);

        delete[] buffer;
    }
    else
    {
        std::cout << "File " << filename << " could not be found" << std::endl;
    }

    return result;
}
