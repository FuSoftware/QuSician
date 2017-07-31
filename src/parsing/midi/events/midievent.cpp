#include "midievent.h"

MidiEvent::MidiEvent(int delta)
{
    this->delta = delta;
    this->absolute = -1;
}

void MidiEvent::generateAbsolute(int previousAbs)
{
    this->absolute = previousAbs + this->delta;
}

void MidiEvent::generateRealTimes(int usPerTick)
{
    this->deltaRt = this->delta * ((float)usPerTick / 1000.0);
    this->absoluteRt = this->absolute * ((float)usPerTick / 1000.0);
}

int MidiEvent::getAbsolute() const
{
    return (this->absolute == -1 ? 0 : this->absolute);
}

int MidiEvent::getDelta() const
{
    return this->delta;
}

MidiEventType MidiEvent::getType() const
{
    return this->type;
}

int MidiEvent::getAbsoluteRt() const
{
    return this->absoluteRt;
}
int MidiEvent::getDeltaRt() const
{
    return this->deltaRt;
}

bool MidiEvent::isMetaEvent() const
{
    return this->isMeta;
}

bool midiEventAbsComp(const MidiEvent* a, const MidiEvent* b)
{
    return a->getAbsolute() < b->getAbsolute();
}
