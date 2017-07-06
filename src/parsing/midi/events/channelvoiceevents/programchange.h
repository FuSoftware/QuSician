#ifndef PROGRAMCHANGE_H
#define PROGRAMCHANGE_H

#include "../midievent.h"
#include <vector>

class ProgramChange : public MidiEvent
{
public:
    ProgramChange(int delta, int n, int p);

    std::vector<unsigned char> getData();

private:
    int program;
    int channel;
};

#endif // PROGRAMCHANGE_H
