#ifndef MIDIEVENT_H
#define MIDIEVENT_H

//https://www.csie.ntu.edu.tw/~r92092/ref/midi/
//https://www.midi.org/specifications/item/table-1-summary-of-midi-message
#include <vector>
#include <string>

enum MidiEventType{
    CHANNEL_PRESSURE = 0,
    CONTROL_CHANGE,
    NOTE_OFF,
    NOTE_ON,
    PITCH_WHEEL_CHANGE,
    POLYPHONIC_KEY_PRESSURE,
    PROGRAM_CHANGE,
    END_OF_TRACK,
    MIDI_CHANNEL_PREFIX,
    SEQUENCE_NUMBER,
    SET_TEMPO,
    SMPTE_OFFSET,
    TEXT_EVENT,
    TIME_SIGNATURE
};


class MidiEvent
{
public:
    MidiEvent(int delta);
    void generateAbsolute(int previousAbs);
    void generateRealTimes(int usPerTick);

    virtual std::vector<unsigned char> getData() = 0;
    int getAbsolute() const;
    int getDelta() const;
    int getAbsoluteRt() const;
    int getDeltaRt() const;
    bool isMetaEvent() const;
    MidiEventType getType() const;

protected:
    int absolute;
    int delta;

    int deltaRt;
    int absoluteRt;
    MidiEventType type;

    bool isMeta;
};

bool midiEventAbsComp(const MidiEvent* a, const MidiEvent* b);

#endif // MIDIEVENT_H
