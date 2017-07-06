#include "noteoff.h"

NoteOff::NoteOff(int delta, int n, int k, int v) : MidiEvent(delta)
{
    this->channel = n;
    this->key = k;
    this->velocity = v;
    this->type = MidiEventType::NOTE_OFF;
    this->isMeta = false;
}

int NoteOff::getChannel()
{
    return this->channel;
}

int NoteOff::getKey()
{
    return this->key;
}

int NoteOff::getVelocity()
{
    return this->velocity;
}

std::vector<unsigned char> NoteOff::getData()
{
    std::vector<unsigned char> message;
    message.push_back(0x80);
    message.push_back(this->key);
    message.push_back(this->velocity);
    return message;
}
