#include "sequencenumber.h"

SequenceNumber::SequenceNumber(int delta) : MidiEvent(delta)
{
    this->type = MidiEventType::SEQUENCE_NUMBER;
    this->isMeta = true;
}

std::vector<unsigned char> SequenceNumber::getData()
{

}
