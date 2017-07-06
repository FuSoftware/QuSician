#ifndef CONVERSION_H
#define CONVERSION_H

#include <cstdint>

class Conversion
{
public:
    Conversion();

    static int toInt(unsigned char data[], int length);
};

#endif // CONVERSION_H
