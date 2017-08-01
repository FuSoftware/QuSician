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

void MidiEvent::generateRealTimes(int usPerTick, int prevAbsRt)
{
    this->deltaRt = this->delta * ((float)usPerTick / 1000.0);

    if(prevAbsRt > 0)
        this->absoluteRt = prevAbsRt + this->deltaRt;
    else
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

MidiEvent *getLastEventBefore(std::vector<MidiEvent*> events, int ticks, MidiEventType type)
{
    MidiEvent *e = 0;

    for(int i=0;i<events.size();i++)
    {
        MidiEvent *t = events[i];

        if(t->getAbsolute() > ticks)
            break;

        if(t->getType() == type)
            e = t;
    }

    return e;
}

int getLastPositionBefore(std::vector<MidiEvent*> events, int ticks, MidiEventType type)
{
    int res = 0;

    for(int i=0;i<events.size();i++)
    {
        MidiEvent *t = events[i];

        if(t->getAbsolute() > ticks)
            break;

        if(t->getType() == type)
            res = i;
    }

    return res;
}
