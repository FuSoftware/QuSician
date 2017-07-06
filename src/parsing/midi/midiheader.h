#ifndef MIDIHEADER_H
#define MIDIHEADER_H

#include <iostream>
#include <vector>
#include <array>
#include <sstream>

#include "./events/midievent.h"
#include "../conversion.h"

using namespace std;

class MidiHeader
{
public:
    MidiHeader();
    MidiHeader(vector<char> data);

    void loadData(vector<char> data);
    string toString();

    int getTrackChunks() const;
    int getDivisions() const;

private:
    string MThd;
    int headerLength;
    int format;
    int trackChunks;
    int divisions;
};

#endif // MIDIHEADER_H
