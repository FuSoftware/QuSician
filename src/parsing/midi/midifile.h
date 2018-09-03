#ifndef MIDIFILE_H
#define MIDIFILE_H

#include <iostream>
#include <vector>
#include <algorithm>

//TODO : Remove
#include <chrono>

struct TimeData
{
    int usPerQuarter;
    int numerator;
    int denominator;
    int clock;
    int thirtySeconds;
};

class SetTempo;
class TimeSignature;
class MidiHeader;
class MidiTrack;
class MidiFile
{
public:
    MidiFile();

    void addtrack(MidiTrack* track);
    void setTracks(std::vector<MidiTrack*> tracks);
    void setFileInfo(MidiTrack *track);
    void setHeader(MidiHeader* header);

    void loadEvents();
    std::vector<MidiTrack*> getTracks();

    std::string toString();
    std::string getTracksInfo();

    TimeData getTimeData();

    int getTickTimeUs(SetTempo* st, TimeSignature *ts);
    int getTickTimeUs();

private:
    MidiHeader *header;
    MidiTrack *fileInfo;
    std::vector<MidiTrack*> tracks;
};

#endif // MIDIFILE_H
