#include "note.h"

Note::Note()
{
    this->start = -1;
    this->startVelocity = -1;
    this->key = -1;
    this->stop = -1;
    this->stopVelocity = -1;
    this->startTime = -1;
    this->stopTime = -1;
}

Note::Note(int start, int key, int velocity)
{
    setNoteOn(start,key,velocity);
    this->stop = -1;
    this->stopVelocity = -1;
    this->startTime = -1;
    this->stopTime = -1;
}

void Note::setNoteOn(int t, int k, int v)
{
    this->start = t;
    this->startVelocity = v;
    this->key = k;

    //Notes : http://www.electronics.dit.ie/staff/tscarff/Music_technology/midi/midi_note_numbers_for_octaves.htm
    this->octave = this->key / 12;
    this->label = static_cast<KeyLabel>(this->key % 12);
}

void Note::setNoteOff(int t, int v)
{
    this->stop = t;
    this->stopVelocity = v;
}

void Note::setTickTime(int us)
{
    this->startTime = this->start * us / 1000;
    this->stopTime = this->stop * us / 1000;
}

Note* Note::getLastOpenKey(vector<Note *> *notes, int key)
{
    for(int i=notes->size()-1;i>=0;i--)
    {
        Note* n = notes->at(i);
        if(n->getKey() == key && n->getStopTicks() == -1)
        {
            return n;
        }
    }

    return 0;
}

int Note::getKey()
{
    return this->key;
}

int Note::getStartTicks()
{
    return this->start;
}

int Note::getStopTicks()
{
    return this->stop;
}

int Note::getStart()
{
    return this->startTime;
}

int Note::getStop()
{
    return this->stopTime;
}

KeyLabel Note::getLabel()
{
    return this->label;
}

int Note::getOctave()
{
    return this->octave;
}

int Note::getStartVelocity()
{
    return this->startVelocity;
}

int Note::getStopVelocity()
{
    return this->stopVelocity;
}


bool isSharp(int key)
{
    int k = key%12;

    switch(k)
    {
    case 1:
    case 3:
    case 6:
    case 8:
    case 10:
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool isSharp(Note* n)
{
    return isSharp(n->getKey());
}
