#include "midiheader.h"

MidiHeader::MidiHeader()
{

}

void MidiHeader::setFormat(int format)
{
    this->format = format;
}

void MidiHeader::setTrackChunks(int chunks)
{
    this->trackChunks = chunks;
}

void MidiHeader::setDivisions(int divisions)
{
    this->divisions = divisions;
}


std::string MidiHeader::toString()
{
    std::ostringstream  ss;
    ss << "Midi header   : " << this->MThd << "\n";
    ss << "Header Length : " << this->headerLength << "\n";
    ss << "Format        : " << this->format << "\n";
    ss << "Track Chunks  : " << this->trackChunks << "\n";
    ss << "Divisions     : " << this->divisions << "\n";

    return ss.str();
}

int MidiHeader::getTrackChunks() const
{
    return this->trackChunks;
}

int MidiHeader::getDivisions() const
{
    return this->divisions;
}
