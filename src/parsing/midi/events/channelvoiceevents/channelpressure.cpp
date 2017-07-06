#include "channelpressure.h"

ChannelPressure::ChannelPressure(int delta, int c, int p) : MidiEvent(delta)
{
    this->channel = c;
    this->pressure = p;
    this->type = MidiEventType::CONTROL_CHANGE;
    this->isMeta = false;
}

std::vector<unsigned char> ChannelPressure::getData()
{
    std::vector<unsigned char> message;
    message.push_back(0xD0);
    message.push_back(this->pressure);
    return message;
}
