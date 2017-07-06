#ifndef PITCHWHEELCHANGE_H
#define PITCHWHEELCHANGE_H

#include "../midievent.h"
#include <vector>

class PitchWheelChange : public MidiEvent
{
public:
    PitchWheelChange(int delta, int n, int l, int m);

    std::vector<unsigned char> getData();

private:
    int channel;
    int value;
    int least;
    int most;
};

#endif // PITCHWHEELCHANGE_H
