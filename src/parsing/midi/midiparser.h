#ifndef MIDIPARSER_H
#define MIDIPARSER_H

#include <iostream>
#include <vector>
#include <algorithm>

class MidiEvent;
class MidiTrack;
class MidiHeader;
class MidiFile;
class MidiParser
{
public:
    MidiParser();

    static std::vector<MidiEvent*> parseEvents(std::vector<unsigned char> data);
    static MidiTrack *parseTrack(std::vector<unsigned char> data);
    static MidiHeader *parseHeader(std::vector<unsigned char> data);
    static MidiFile *parseFile(std::string path);

private:

};

#endif // MIDIPARSER_H
