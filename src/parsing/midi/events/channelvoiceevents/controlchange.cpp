#include "controlchange.h"

ControlChange::ControlChange(int delta, int n, int c, int v) : MidiEvent(delta)
{
    this->channel = n;
    this->controller = c;
    this->value = v;
    this->type = MidiEventType::CONTROL_CHANGE;
    this->isMeta = false;
}

std::vector<unsigned char> ControlChange::getData()
{
    std::vector<unsigned char> message;
    message.push_back(0xB0);
    message.push_back(this->controller);
    message.push_back(this->value);
    return message;
}
