#ifndef SETTEMPO_H
#define SETTEMPO_H

#include "../midievent.h"

class SetTempo : public MidiEvent
{
public:
    SetTempo(int delta, int m);
    int getTempo();
    std::vector<unsigned char> getData();

private:
    int microseconds;
};

#endif // SETTEMPO_H
