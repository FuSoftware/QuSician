#ifndef PARTITION_H
#define PARTITION_H

#include <iostream>
#include <fstream>
#include <vector>

#include "note.h"
#include "parsing/midi/miditrack.h"

using namespace std;

struct TimeInfo
{
    int numerator;
    int denominator;
    int clock;
    int thrityNotes;
};

class Partition
{
public:
    Partition();
    Partition(MidiTrack* track);
    void setTickTime(int usPerTick);

    std::vector<Note *> *getNotes();
    void toCSV(std::string path, std::string delimiter);

    static std::vector<Note *> *loadMidiTrack(MidiTrack* track);

private :
    std::vector<Note*> *notes;

};

#endif // PARTITION_H
