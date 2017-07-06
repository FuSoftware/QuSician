#ifndef TEXTEVENT_H
#define TEXTEVENT_H

#include <iostream>

#include "../midievent.h"

using namespace std;

enum TextEventType
{
    COPYRIGHT_NOTICE = 0x02,
    SEQUENCE_TRACK_NAME = 0x03,
    INSTRUMENT_NAME = 0x04,
    LYRIC = 0x05,
    MARKER = 0x06,
    CUE_POINT = 0x07
};

class TextEvent : public MidiEvent
{
public:
    TextEvent(int delta, string text, TextEventType type);
    std::vector<unsigned char> getData();

private:
    string text;
    TextEventType textType;

};

#endif // TESTEVENT_H
