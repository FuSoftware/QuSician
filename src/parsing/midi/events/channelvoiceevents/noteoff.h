#ifndef NOTEOFF_H
#define NOTEOFF_H

#include "../midievent.h"
#include <vector>

class NoteOff : public MidiEvent
{
public:
    NoteOff(int delta, int n, int k, int v);

    int getChannel();
    int getKey();
    int getVelocity();

    std::vector<unsigned char> getData();

private:
    int channel;
    int key;
    int velocity;
};

#endif // NOTEOFF_H
