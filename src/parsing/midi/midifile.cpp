#include "midifile.h"

MidiFile::MidiFile()
{

}

MidiFile::MidiFile(string file)
{
    loadFile(file);
}

void MidiFile::loadFile(string file)
{
    vector<char> data = FileReader::ReadAllBytes(file);
    vector<char> headerData(data.begin(), data.begin()+14);

    header.loadData(headerData);

    vector<unsigned char> remainingBytes(data.begin() + 14, data.end());

    int i=0;

    while(remainingBytes.size() > 0)
    {
        MidiTrack *t = new MidiTrack(remainingBytes);

        if(i==0)
            this->fileInfo = t;

        tracks.push_back(t);

        i++;
        remainingBytes.erase(remainingBytes.begin(),remainingBytes.begin()+t->getLength());
    }

    //Compute real times
    for(int i=0;i<this->tracks.size();i++)
    {
        MidiTrack *t = this->tracks[i];
        for(int j=0;j<t->getEventCount();j++)
        {
            MidiEvent *e = t->getEvents()[j];
            e->generateRealTimes(this->getTickTimeUs());
        }
    }
}

string MidiFile::toString()
{
    return header.toString() + "\n" + getTracksInfo();
}

string MidiFile::getTracksInfo()
{
    ostringstream  ss;

    for(unsigned int i=0;i<tracks.size();i++)
    {
        ss << "Track " << i+1 << endl << tracks[i]->toString() << endl;
    }

    return ss.str();
}

vector<MidiTrack*> MidiFile::getTracks()
{
    return this->tracks;
}

TimeData MidiFile::getTimeData()
{
    TimeSignature* ts = 0;
    SetTempo *st = 0;

    vector<MidiEvent*> events = fileInfo->getEvents();
    for(int i=0;i<events.size();i++)
    {
        if(events[i]->getType() == MidiEventType::TIME_SIGNATURE)
        {
            ts = (TimeSignature*)events[i];
        }
        else if(events[i]->getType() == MidiEventType::SET_TEMPO)
        {
            st = (SetTempo*)events[i];
        }
    }

    TimeData d;
    d.usPerQuarter = 0;

    if(ts == 0 || st == 0)
        return d;


    d.usPerQuarter = st->getTempo();
    d.clock = ts->getClock();
    d.denominator = ts->getDenominator();
    d.numerator = ts->getNumerator();
    d.thirtySeconds = ts->getThirtySeconds();
    return d;
}

int MidiFile::getTickTimeUs()
{
    //http://www.lastrayofhope.co.uk/2009/12/23/midi-delta-time-ticks-to-seconds/
    TimeData d = this->getTimeData();
    int usPerBeat = d.usPerQuarter == 0 ? 500000 : d.usPerQuarter;
    int tickPerBeat = header.getDivisions() * d.denominator /d.numerator;
    int usPerTick = (usPerBeat / tickPerBeat);
    return usPerTick;
}
