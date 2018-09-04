#include "miditrack.h"

MidiTrack::MidiTrack()
{

}

void MidiTrack::setEvents(std::vector<MidiEvent*> events)
{
    this->events = events;
}


std::string MidiTrack::toString()
{
    std::ostringstream  ss;
    ss << "Events        : " << this->events.size() << "\n";
    return ss.str();
}

int MidiTrack::getLength()
{
    return this->length; //Track size + header size
}

void MidiTrack::setLength(int length)
{
    this->length = length;
}

std::vector<MidiEvent*> MidiTrack::getEvents()
{
    return this->events;
}

std::vector<MidiEvent*> MidiTrack::getNoteEvents()
{
    std::vector<MidiEvent*> events;

    for(int i=0;i<this->events.size();i++)
    {
        MidiEvent *e = this->events[i];

        if(e->getType() == MidiEventType::NOTE_ON || e->getType() == MidiEventType::NOTE_OFF)
            events.push_back(e);
    }

    return events;
}

std::vector<MidiEvent*> MidiTrack::getChannelEvents()
{
    std::vector<MidiEvent*> events;

    for(int i=0;i<this->events.size();i++)
    {
        MidiEvent *e = this->events[i];

        if(!e->isMetaEvent())
            events.push_back(e);
    }

    return events;
}


int MidiTrack::getEventCount()
{
    return this->events.size();
}
