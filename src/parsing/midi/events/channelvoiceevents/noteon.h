#ifndef NOTEON_H
#define NOTEON_H

#include "../midievent.h"
#include <vector>

class NoteOn : public MidiEvent
{
public:
    NoteOn(int delta, int n, int k, int v);

    int getChannel();
    int getKey();
    int getVelocity();

    std::vector<unsigned char> getData();

private:
    int channel;
    int key;
    int velocity;
};

#endif // NOTEON_H
