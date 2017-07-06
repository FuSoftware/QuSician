#ifndef ENDOFTRACK_H
#define ENDOFTRACK_H

#include "../midievent.h"

class EndOfTrack : public MidiEvent
{
public:
    EndOfTrack(int delta);
    std::vector<unsigned char> getData();
};

#endif // ENDOFTRACK_H
