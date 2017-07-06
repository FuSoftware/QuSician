#include "midichannelprefix.h"

MidiChannelPrefix::MidiChannelPrefix(int delta, int cc) : MidiEvent(delta)
{
    this->channel = cc;
    this->type = MidiEventType::MIDI_CHANNEL_PREFIX;
    this->isMeta = true;
}


std::vector<unsigned char> MidiChannelPrefix::getData()
{

}
