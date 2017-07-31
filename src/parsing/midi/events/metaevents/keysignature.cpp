#include "keysignature.h"

KeySignature::KeySignature(int delta, int sf, int mi) : MidiEvent(delta)
{
    this->sf = sf;
    this->mi = mi;
}

std::vector<unsigned char> KeySignature::getData()
{
    std::vector<unsigned char> data;
    return data;
}

bool KeySignature::isMinor()
{
    return this->mi > 0;
}

int KeySignature::getKey()
{
    return this->sf;
}
