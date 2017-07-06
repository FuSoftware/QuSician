#include "pitchwheelchange.h"

PitchWheelChange::PitchWheelChange(int delta, int n, int l, int m) : MidiEvent(delta)
{
    this->channel = n;
    this->most = m;
    this->least = l;
    this->type = MidiEventType::PITCH_WHEEL_CHANGE;
    this->isMeta = false;
}

std::vector<unsigned char> PitchWheelChange::getData()
{
    std::vector<unsigned char> message;
    message.push_back(0xE0);
    message.push_back(this->least);
    message.push_back(this->most);
    return message;
}
