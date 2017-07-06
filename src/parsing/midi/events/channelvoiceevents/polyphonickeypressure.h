#ifndef POLYPHONICKEYPRESSURE_H
#define POLYPHONICKEYPRESSURE_H

#include "../midievent.h"
#include <vector>

class PolyphonicKeyPressure : public MidiEvent
{
public:
    PolyphonicKeyPressure(int delta, int n, int k, int v);

    std::vector<unsigned char> getData();

private:
    int channel;
    int velocity;
    int key;
};

#endif // POLYPHONICKEYPRESSURE_H
