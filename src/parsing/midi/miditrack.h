#ifndef MIDITRACK_H
#define MIDITRACK_H

#include <iostream>
#include <vector>
#include <sstream>
#include "variablelengthvalue.h"

#include "events/events.h"
#include "../conversion.h"

class MidiTrack
{
public:
    MidiTrack();
    MidiTrack(std::vector<unsigned char> data);
    void load(std::vector<unsigned char> data);
    std::string toString();

    int getLength();
    std::vector<MidiEvent*> getEvents();
    std::vector<MidiEvent*> getNoteEvents();
    std::vector<MidiEvent*> getChannelEvents();
    int getEventCount();

    static vector<MidiEvent*> parseEvents(std::vector<unsigned char> data);

private:
    void loadEvents(vector<unsigned char> data);

    std::string MTrk;
    int length;
    std::vector<MidiEvent*> events;
};

#endif // MIDITRACK_H
