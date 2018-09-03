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
    std::string toString();

    void setEvents(std::vector<MidiEvent*> events);

    int getLength();
    void setLength(int length);
    std::vector<MidiEvent*> getEvents();
    std::vector<MidiEvent*> getNoteEvents();
    std::vector<MidiEvent*> getChannelEvents();
    int getEventCount();

private:
    std::vector<MidiEvent*> events;
    int length;
};

#endif // MIDITRACK_H
