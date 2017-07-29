#ifndef MIDITRACK_H
#define MIDITRACK_H

#include <iostream>
#include <vector>
#include <sstream>
#include "variablelengthvalue.h"

#include "events/events.h"
#include "../conversion.h"

using namespace std;

class MidiTrack
{
public:
    MidiTrack();
    MidiTrack(vector<unsigned char> data);
    void load(vector<unsigned char> data);
    string toString();

    int getLength();
    vector<MidiEvent*> getEvents();
    int getEventCount();

    static vector<MidiEvent*> parseEvents(vector<unsigned char> data);

private:
    void loadEvents(vector<unsigned char> data);

    string MTrk;
    int length;
    vector<MidiEvent*> events;
};

#endif // MIDITRACK_H
