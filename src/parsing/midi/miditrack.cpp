#include "miditrack.h"

MidiTrack::MidiTrack()
{

}

MidiTrack::MidiTrack(vector<unsigned char> data)
{
    load(data);
}

bool MidiTrack::load(vector<unsigned char> data)
{
    //MThd - 4 bytes
    unsigned char MTrkBuffer[4];

    for(int i=0;i<4;i++)
        MTrkBuffer[i] = data[i];

    this->MTrk = string(MTrkBuffer, MTrkBuffer + 4);

    if(MTrk != "MTrk")
    {
        cerr << "Error while parsing track, MTrk header not found" << endl;
        this->loaded = false;
        return false;
    }

    //Length - 4 bytes
    unsigned char lengthBuffer[4];

    for(int i=0;i<4;i++)
        lengthBuffer[i] = data[i+4];

    this->length = Conversion::toInt(lengthBuffer,4);

    //Data
    vector<unsigned char> trackData(data.begin() + 8, data.begin() + 8 + this->length);
    loadEvents(trackData);

    this->loaded = true;
    return true;
}

void MidiTrack::loadEvents(vector<unsigned char> data)
{
    this->events = parseEvents(data);
}

vector<MidiEvent*> MidiTrack::parseEvents(vector<unsigned char> data)
{
    vector<MidiEvent*> events;
    VLV vlv;
    unsigned int i=0;

    while(i<data.size())
    {
        //Delta
        vlv.addData(data[i]);
        i++;

        if(i>= data.size())
            break;

        //MIDI Events
        if(((data[i] & 0x80) >= 0x80) && ((data[i] & 0x80) <= 0xEE))
        {
            int delta = vlv.toInt();
            int status = (data[i] >> 4);
            int n = (data[i] & 0x0F);

            switch (status)
            {
            case 8:
                //Note Off event.
                events.push_back(new NoteOff(delta, n, data[++i], data[++i]));
                break;
            case 9:
                //Note On event.
                events.push_back(new NoteOn(delta, n, data[++i], data[++i]));
                break;
            case 10:
                //Polyphonic Key Pressure (Aftertouch).
                events.push_back(new PolyphonicKeyPressure(delta, n, data[++i], data[++i]));
                break;
            case 11:
                //Control Change
                events.push_back(new ControlChange(delta, n, data[++i], data[++i]));
                break;
            case 12:
                //Program Change
                events.push_back(new ProgramChange(delta, n, data[++i]));
                break;
            case 13:
                //Channel Pressure
                events.push_back(new ChannelPressure(delta, n, data[++i]));
                break;
            case 14:
                //Pitch Wheel Change
                events.push_back(new PitchWheelChange(delta, n, data[++i], data[++i]));
                break;
            }


            //Meta Events
            if (data[i] == 0xFF)
            {
                i++;
                if(data[i] >= 0x01 && data[i] <= 0x0F)
                {
                    //Text Event
                    int eventType = data[i];
                    i++;
                    int len = data[i];
                    char text[len];
                    for (int j = 0; j < len; j++)
                        text[j] = data[++i];

                    string s(text, text + len);
                    events.push_back(new TextEvent(delta, s, (TextEventType)eventType));
                }
                else
                {
                    switch (data[i])
                    {
                        case 0x00:
                            //FF 00 02 Sequence Number
                            break;
                        case 0x20:
                            //FF 20 01 cc MIDI Channel Prefix
                            if (data[++i] == 0x20)
                                if (data[++i] == 0x01)
                                    events.push_back(new MidiChannelPrefix(delta, data[++i]));
                            break;
                        case 0x2F:
                            //FF 2F 00 End of Track
                            if (data[++i] == 0x00)
                                events.push_back(new EndOfTrack(delta));
                            break;
                        case 0x51:
                            //FF 51 03 tttttt Set Tempo (in microseconds per MIDI quarter-note)
                            if (data[++i] == 0x03)
                            {
                                unsigned char tempoBuffer[3];
                                for (int j = 0; j < 3; j++)
                                    tempoBuffer[j] = data[++i];

                                int tempo = Conversion::toInt(tempoBuffer,3);
                                events.push_back(new SetTempo(delta, tempo));
                            }
                            break;
                        case 0x54:
                            //FF 54 05 hr mn se fr ff SMPTE Offset
                            if (data[++i] == 0x05)
                                events.push_back(new SMPTEOffset(delta, data[++i], data[++i], data[++i], data[++i], data[++i]));
                            break;
                        case 0x58:
                            //FF 58 04 nn dd cc bb Time Signature
                            if (data[++i] == 0x04)
                                events.push_back(new TimeSignature(delta, data[++i], data[++i], data[++i], data[++i]));
                            break;
                        case 0x59:
                            //FF 59 02 sf mi Key Signature
                            if (data[++i] == 0x02)
                                events.push_back(new KeySignature(delta, data[++i], data[++i]));
                            break;
                    }
                }
            }
            i++;
            vlv.clear();
        }
    }

    //Compute absolute times
    for(int i=1;i<events.size();i++)
    {
        events[i]->generateAbsolute(events[i-1]->getAbsolute());
    }

    return events;
}

std::string MidiTrack::toString()
{
    std::ostringstream  ss;
    ss << "Midi header   : " << this->MTrk << "\n";
    ss << "Track Length  : " << this->length << "\n";
    ss << "Events        : " << this->events.size() << "\n";
    return ss.str();
}

bool MidiTrack::isLoaded()
{
    return this->loaded;
}

int MidiTrack::getLength()
{
    return this->length + 8;
}

std::vector<MidiEvent*> MidiTrack::getEvents()
{
    return this->events;
}

std::vector<MidiEvent*> MidiTrack::getNoteEvents()
{
    std::vector<MidiEvent*> events;

    for(int i=0;i<this->events.size();i++)
    {
        MidiEvent *e = this->events[i];

        if(e->getType() == MidiEventType::NOTE_ON || e->getType() == MidiEventType::NOTE_OFF)
            events.push_back(e);
    }

    return events;
}

std::vector<MidiEvent*> MidiTrack::getChannelEvents()
{
    std::vector<MidiEvent*> events;

    for(int i=0;i<this->events.size();i++)
    {
        MidiEvent *e = this->events[i];

        if(!e->isMetaEvent())
            events.push_back(e);
    }

    return events;
}


int MidiTrack::getEventCount()
{
    return this->events.size();
}
