#ifndef CHANNELPRESSURE_H
#define CHANNELPRESSURE_H

#include "../midievent.h"
#include <vector>

class ChannelPressure : public MidiEvent
{
public:
    ChannelPressure(int delta, int c, int p);

    std::vector<unsigned char> getData();

private:
    int pressure;
    int channel;
};

#endif // CHANNELPRESSURE_H
