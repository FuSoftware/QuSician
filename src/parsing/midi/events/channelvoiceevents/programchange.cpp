#include "programchange.h"

ProgramChange::ProgramChange(int delta, int n, int p) : MidiEvent(delta)
{
    this->program = p;
    this->channel = n;
    this->type = MidiEventType::PROGRAM_CHANGE;
    this->isMeta = false;
}

std::vector<unsigned char> ProgramChange::getData()
{
    std::vector<unsigned char> message;
    message.push_back(0xC0);
    message.push_back(this->program);
    return message;
}
