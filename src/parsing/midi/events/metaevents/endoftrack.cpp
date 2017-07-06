#include "endoftrack.h"

EndOfTrack::EndOfTrack(int delta) : MidiEvent(delta)
{
    this->type = MidiEventType::END_OF_TRACK;
    this->isMeta = true;
}


std::vector<unsigned char> EndOfTrack::getData()
{

}
