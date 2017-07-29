#include "midiheader.h"

MidiHeader::MidiHeader()
{

}

MidiHeader::MidiHeader(vector<unsigned char> data)
{
    loadData(data);
}

void MidiHeader::loadData(vector<unsigned char> data)
{
    //MThd - 4 bytes
    unsigned char MThdBuffer[4];

    for(int i=0;i<4;i++)
        MThdBuffer[i] = data[i];

    this->MThd = string(MThdBuffer, MThdBuffer + 4);

    //Header Length - 4 bytes
    unsigned char headerLengthBuffer[4];

    for(int i=0;i<4;i++)
        headerLengthBuffer[i] = data[i+4];

    this->headerLength = Conversion::toInt(headerLengthBuffer,4);

    //Format - 2 bytes
    unsigned char formatBuffer[2];

    for(int i=0;i<2;i++)
        formatBuffer[i] = data[i+8];

    this->format = Conversion::toInt(formatBuffer,2);

    //Number of track chunks - 2 bytes
    unsigned char trackChunksBuffer[2];

    for(int i=0;i<2;i++)
        trackChunksBuffer[i] = data[i+10];

    this->trackChunks = Conversion::toInt(trackChunksBuffer,2);

    //Divisions - 2 bytes
    unsigned char divisionsBuffer[2];

    for(int i=0;i<2;i++)
        divisionsBuffer[i] = data[i+12];

    this->divisions = Conversion::toInt(divisionsBuffer,2);
}

string MidiHeader::toString()
{
    ostringstream  ss;
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
