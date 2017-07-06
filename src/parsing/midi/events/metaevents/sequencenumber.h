#ifndef SEQUENCENUMBER_H
#define SEQUENCENUMBER_H

#include "../midievent.h"

class SequenceNumber : public MidiEvent
{
public:
    SequenceNumber(int delta);
    std::vector<unsigned char> getData();
};

#endif // SEQUENCENUMBER_H
