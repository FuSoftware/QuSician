#ifndef SMPTEOFFSET_H
#define SMPTEOFFSET_H

#include "../midievent.h"

class SMPTEOffset : public MidiEvent
{
public:
    SMPTEOffset(int delta, int h, int m, int s, int fr, int ff);
    std::vector<unsigned char> getData();

private:
    int hour;
    int minutes;
    int seconds;
    int FR;
    int fractionalFrames;
};

#endif // SMPTEOFFSET_H
