#include "settempo.h"

SetTempo::SetTempo(int delta, int m) : MidiEvent(delta)
{
    this->microseconds = m;
    this->type = MidiEventType::SET_TEMPO;
    this->isMeta = true;
}

int SetTempo::getTempo() const
{
    return this->microseconds;
}

std::vector<unsigned char> SetTempo::getData()
{

}
