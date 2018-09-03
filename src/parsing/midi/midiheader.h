#ifndef MIDIHEADER_H
#define MIDIHEADER_H

#include <iostream>
#include <vector>
#include <array>
#include <sstream>

#include "./events/midievent.h"
#include "../conversion.h"

class MidiHeader
{
public:
    MidiHeader();

    void setFormat(int format);
    void setTrackChunks(int chunks);
    void setDivisions(int divisions);

    std::string toString();

    int getTrackChunks() const;
    int getDivisions() const;

private:
    std::string MThd;
    int headerLength;
    int format;
    int trackChunks;
    int divisions;
};

#endif // MIDIHEADER_H
