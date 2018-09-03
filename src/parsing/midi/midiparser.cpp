#include "midiparser.h"
#include "parsing/filereader.h"
#include "parsing/conversion.h"

#include "parsing/midi/midifile.h"
#include "parsing/midi/midiheader.h"
#include "parsing/midi/miditrack.h"
#include "parsing/midi/events/events.h"

MidiParser::MidiParser()
{

}

std::vector<MidiEvent*> MidiParser::parseEvents(std::vector<unsigned char> data)
{
    std::vector<MidiEvent*> events;
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

                    std::string s(text, text + len);
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

MidiTrack *MidiParser::parseTrack(std::vector<unsigned char> data)
{
    MidiTrack *track = new MidiTrack();

    //MThd - 4 bytes
    unsigned char MTrkBuffer[4];

    for(int i=0;i<4;i++)
        MTrkBuffer[i] = data[i];

    std::string MTrk = std::string(MTrkBuffer, MTrkBuffer + 4);

    if(MTrk != "MTrk")
    {
        std::cerr << "Error while parsing track, MTrk header not found" << std::endl;
        return nullptr;
    }

    //Length - 4 bytes
    unsigned char lengthBuffer[4];

    for(int i=0;i<4;i++)
        lengthBuffer[i] = data[i+4];

    track->setLength(Conversion::toInt(lengthBuffer,4));

    //Data
    std::vector<unsigned char> trackData(data.begin() + 8, data.begin() + 8 + track->getLength());
    std::vector<MidiEvent*> events = parseEvents(trackData);

    track->setEvents(events);
    return track;
}

MidiHeader *MidiParser::parseHeader(std::vector<unsigned char> data)
{
    MidiHeader *header = new MidiHeader();
    //MThd - 4 bytes
    unsigned char MThdBuffer[4];
    std::string mthd;

    for(int i=0;i<4;i++)
        MThdBuffer[i] = data[i];

    mthd = std::string(MThdBuffer, MThdBuffer + 4);
    if(mthd.compare("MThd") != 0)
    {
        std::cout << "Header MThd is invalid : " << mthd << std::endl;
        return nullptr;
    }

    //Header Length - 4 bytes
    unsigned char headerLengthBuffer[4];
    int headerLength = 0;

    for(int i=0;i<4;i++)
        headerLengthBuffer[i] = data[i+4];

    headerLength = Conversion::toInt(headerLengthBuffer,4);

    //Format - 2 bytes
    unsigned char formatBuffer[2];

    for(int i=0;i<2;i++)
        formatBuffer[i] = data[i+8];

    header->setFormat(Conversion::toInt(formatBuffer,2));

    //Number of track chunks - 2 bytes
    unsigned char trackChunksBuffer[2];

    for(int i=0;i<2;i++)
        trackChunksBuffer[i] = data[i+10];

    header->setTrackChunks(Conversion::toInt(trackChunksBuffer,2));

    //Divisions - 2 bytes
    unsigned char divisionsBuffer[2];

    for(int i=0;i<2;i++)
        divisionsBuffer[i] = data[i+12];

    header->setDivisions(Conversion::toInt(divisionsBuffer,2));

    return header;
}

MidiFile * MidiParser::parseFile(std::string path)
{
    std::vector<unsigned char> data = FileReader::ReadAllBytes(path);
    std::vector<unsigned char> headerData(data.begin(), data.begin()+14);

    MidiFile* file = new MidiFile();
    MidiHeader* header = parseHeader(headerData);
    file->setHeader(header);

    std::vector<unsigned char> remainingBytes(data.begin() + 14, data.end());
    std::vector<MidiTrack*> tracks;

    int i=0;

    while(remainingBytes.size() > 0)
    {
        MidiTrack *t = parseTrack(remainingBytes);

        if(t == nullptr)
        {
            std::cerr << "Track " << i << " from " << file << " could not be loaded" << std::endl;
        }
        else
        {
            tracks.push_back(t);
        }

        i++;
        remainingBytes.erase(remainingBytes.begin(),remainingBytes.begin()+t->getLength());
    }

    file->setFileInfo(tracks[i]);
    file->setTracks(tracks);
    file->loadEvents();

    return file;
}
