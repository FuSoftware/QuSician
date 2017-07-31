#ifndef KEYSIGNATURE_H
#define KEYSIGNATURE_H

#include "../midievent.h"

/*
Key Signature, expressed as the number of sharps or flats, and a major/minor flag.
0 represents a key of C, negative numbers represent 'flats', while positive numbers represent 'sharps'.
*/

class KeySignature : public MidiEvent
{
public:
    KeySignature(int delta, int sf, int mi);
    std::vector<unsigned char> getData();

    bool isMinor();
    int getKey();

private:
    int sf;
    int mi;
};

#endif // KEYSIGNATURE_H
