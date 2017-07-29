#include "variablelengthvalue.h"

VariableLengthValue::VariableLengthValue()
{

}

void VariableLengthValue::addData(unsigned char c)
{
    this->data.push_back(c);
}

bool VariableLengthValue::isComplete()
{
    if(this->data.empty())
        return false;

    unsigned char c = this->data.back();
    return c < 0x80;
}

int VariableLengthValue::toInt()
{
    std::vector<unsigned char> c = this->decompress();

    int res = 0;
    int offset = 0;

    for(int i=0; i<c.size(); i++)
    {
        res = (c[i] << offset) | res;
        offset += 8;
    }

    return res;
}

int VariableLengthValue::size()
{
    return this->data.size();
}

void VariableLengthValue::clear()
{
    return this->data.clear();
}

std::vector<unsigned char> VariableLengthValue::decompress()
{
    std::vector<bool> b;
    std::vector<bool> buffer;

    for(int i=this->data.size()-1;i>=0;i--)
    {
        buffer = charToBitArray(data[i]);
        buffer.pop_back();
        b.insert(b.end(),buffer.begin(),buffer.end());
    }

    std::vector<unsigned char> c = bitArrayToCharArray(b);
    return c;
}

unsigned char VariableLengthValue::bitArrayToChar(std::vector<bool> b)
{
    unsigned char c = 0;

    for(int i=0;i<b.size();i++)
    {
        if(b[i])
            c += 1 << i;
    }

    return c;
}

std::vector<unsigned char> VariableLengthValue::bitArrayToCharArray(std::vector<bool> b)
{
    std::vector<unsigned char> c;

    while(b.size() > 0)
    {
        int l = b.size() >= 8 ? 8 : b.size();

        std::vector<bool> buffer(b.begin(), b.begin() + l);
        c.push_back(bitArrayToChar(buffer));

        b.erase(b.begin(), b.begin() + l);
    }

    return c;
}

std::vector<bool> VariableLengthValue::charToBitArray(unsigned char c)
{
    std::vector<bool> b;

    for(int i=0;i<8;i++)
    {
        b.push_back((c >> i) & 1);
    }

    return b;
}
