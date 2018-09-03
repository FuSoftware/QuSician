#include "textevent.h"

TextEvent::TextEvent(int delta, std::string text, TextEventType type) : MidiEvent(delta)
{
    this->text = text;
    this->textType = type;
    this->type = MidiEventType::TEXT_EVENT;
    this->isMeta = true;
}

std::vector<unsigned char> TextEvent::getData()
{

}
