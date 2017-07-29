#ifndef VLV_H
#define VLV_H

#include <vector>

//http://www.ccarh.org/courses/253/handout/vlv/

//All std::vector<bool> are stored in LSB
//0b10101110 -> [0,1,1,1,0,1,0,1]

class VariableLengthValue
{
public:
    VariableLengthValue();
    void addData(unsigned char c);
    bool isComplete();
    int toInt();
    int size();

    void clear();

    std::vector<unsigned char> decompress();

    static unsigned char bitArrayToChar(std::vector<bool> b);
    static std::vector<unsigned char> bitArrayToCharArray(std::vector<bool> b);
    static std::vector<bool> charToBitArray(unsigned char c);

private:
    std::vector<unsigned char> data;
};

typedef VariableLengthValue VLV;

#endif // VLV_H
