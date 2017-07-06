#include "noteon.h"

NoteOn::NoteOn(int delta, int n, int k, int v) : MidiEvent(delta)
{
    this->channel = n;
    this->key = k;
    this->velocity = v;
    this->type = MidiEventType::NOTE_ON;
    this->isMeta = false;
}

int NoteOn::getChannel()
{
    return this->channel;
}

int NoteOn::getKey()
{
    return this->key;
}

int NoteOn::getVelocity()
{
    return this->velocity;
}

std::vector<unsigned char> NoteOn::getData()
{
    std::vector<unsigned char> message;
    message.push_back(0x90);
    message.push_back(this->key);
    message.push_back(this->velocity);
    return message;
}
