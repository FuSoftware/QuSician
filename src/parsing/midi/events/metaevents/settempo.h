#ifndef SETTEMPO_H
#define SETTEMPO_H

#include "../midievent.h"

class SetTempo : public MidiEvent
{
public:
    SetTempo(int delta = 0, int m = SetTempo::DEFAULT_TEMPO);
    int getTempo() const;
    std::vector<unsigned char> getData();

    const static int DEFAULT_TEMPO = 500000;

private:
    int microseconds;
};

#endif // SETTEMPO_H
