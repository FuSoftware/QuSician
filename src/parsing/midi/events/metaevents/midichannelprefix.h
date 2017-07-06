#ifndef MIDICHANNELPREFIX_H
#define MIDICHANNELPREFIX_H

#include "../midievent.h"

class MidiChannelPrefix : public MidiEvent
{
public:
    MidiChannelPrefix(int delta, int cc);
    std::vector<unsigned char> getData();

private:
    int channel;
};

#endif // MIDICHANNELPREFIX_H
