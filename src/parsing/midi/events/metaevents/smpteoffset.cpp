#include "smpteoffset.h"

SMPTEOffset::SMPTEOffset(int delta, int h, int m, int s, int fr, int ff) : MidiEvent(delta)
{
    this->hour = h;
    this->minutes = m;
    this->seconds = s;
    this->FR = fr;
    this->fractionalFrames = ff;
    this->type = MidiEventType::SMPTE_OFFSET;
    this->isMeta = true;
}

std::vector<unsigned char> SMPTEOffset::getData()
{

}
