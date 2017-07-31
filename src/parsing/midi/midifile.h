#ifndef MIDIFILE_H
#define MIDIFILE_H

#include <iostream>
#include <vector>
#include <algorithm>

#include "../filereader.h"
#include "midiheader.h"
#include "miditrack.h"

//TODO : Remove
#include <chrono>

using namespace std;

struct TimeData
{
    int usPerQuarter;
    int numerator;
    int denominator;
    int clock;
    int thirtySeconds;
};

class MidiFile
{
public:
    MidiFile();
    MidiFile(string file);

    void loadFile(string file);

    vector<MidiTrack*> getTracks();

    string toString();
    string getTracksInfo();

    MidiHeader header;

    TimeData getTimeData();

    int getTickTimeUs(SetTempo* st, TimeSignature *ts);
    int getTickTimeUs();

private:
    MidiTrack *fileInfo;
    vector<MidiTrack*> tracks;
};

#endif // MIDIFILE_H
