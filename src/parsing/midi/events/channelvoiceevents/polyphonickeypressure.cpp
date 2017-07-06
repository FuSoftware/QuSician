#include "polyphonickeypressure.h"

PolyphonicKeyPressure::PolyphonicKeyPressure(int delta, int n, int k, int v) : MidiEvent(delta)
{
    this->channel = n;
    this->key = k;
    this->velocity = v;
    this->type = MidiEventType::POLYPHONIC_KEY_PRESSURE;
    this->isMeta = false;
}

std::vector<unsigned char> PolyphonicKeyPressure::getData()
{
    std::vector<unsigned char> message;
    message.push_back(0xA0);
    message.push_back(this->key);
    message.push_back(this->velocity);
    return message;
}
