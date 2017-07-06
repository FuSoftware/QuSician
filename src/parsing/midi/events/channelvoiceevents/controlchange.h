#ifndef CONTROLCHANGE_H
#define CONTROLCHANGE_H

#include "../midievent.h"
#include <vector>

class ControlChange : public MidiEvent
{
public:
    ControlChange(int delta, int n, int c, int v);

    std::vector<unsigned char> getData();

private:
    int channel;
    int controller;
    int value;
};

#endif // CONTROLCHANGE_H
