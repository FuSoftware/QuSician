#include "conversion.h"

Conversion::Conversion()
{

}

int Conversion::toInt(unsigned char data[], int length)
{
    int offset = 0;
    int res = 0;

    //for(int i=0;i<length;i++)
    for(int i=length-1;i>=0;i--)
    {
        res = (data[i] << offset) | res;
        offset += 8;
    }


    return res;
}
