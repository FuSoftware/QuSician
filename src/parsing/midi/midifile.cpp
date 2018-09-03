#include "midifile.h"
#include "midiheader.h"
#include "miditrack.h"
#include "events/events.h"

MidiFile::MidiFile()
{

}

std::string MidiFile::toString()
{
    return header->toString() + "\n" + getTracksInfo();
}

void MidiFile::addtrack(MidiTrack* track)
{
    this->tracks.push_back(track);
}

void MidiFile::setTracks(std::vector<MidiTrack*> tracks)
{
    this->tracks = tracks;
}

void MidiFile::setFileInfo(MidiTrack *track)
{
    this->fileInfo = track;
}


void MidiFile::setHeader(MidiHeader* header)
{
    this->header = header;
}

std::string MidiFile::getTracksInfo()
{
    std::ostringstream  ss;

    for(unsigned int i=0;i<tracks.size();i++)
    {
        ss << "Track " << i << std::endl << tracks[i]->toString() << std::endl;
    }

    return ss.str();
}

std::vector<MidiTrack*> MidiFile::getTracks()
{
    return this->tracks;
}

void MidiFile::loadEvents()
{
    //Compute absolute times and store SetTempo Events
    std::vector<MidiEvent*> tempo;
    std::vector<MidiEvent*> timeSignature;

    for(unsigned int i=0;i<tracks.size();i++)
    {
        MidiTrack *t = tracks[i];
        for(int j=0;j<t->getEventCount();j++)
        {
            MidiEvent *e = t->getEvents()[j];
            int prevAbs = j > 0 ? t->getEvents()[j-1]->getAbsolute() : 0;
            e->generateAbsolute(prevAbs);

            if(e->getType() == MidiEventType::SET_TEMPO)
                tempo.push_back(e);
            else if(e->getType() == MidiEventType::TIME_SIGNATURE)
                timeSignature.push_back(e);
        }
    }

    std::sort(timeSignature.begin(),timeSignature.end(),midiEventAbsComp);
    std::sort(tempo.begin(),tempo.end(),midiEventAbsComp);

    //Compute RT for each track
    for(unsigned int i=0;i<this->tracks.size();i++)
    {
        MidiTrack *t = this->tracks[i];

        int cTs = timeSignature.size() > 0 ? 0 : -1;
        int cSt = tempo.size() > 0 ? 0 : -1;
        int nTs = cTs+1 >= timeSignature.size() ? -1 : cTs+1;
        int nSt = cSt+1 >= tempo.size() ? -1 : cSt+1;

        //For each event
        for(int j=0;j<t->getEventCount();j++)
        {
            MidiEvent *e = t->getEvents()[j];

            //Time Signature
            if(nTs>=0)
            {
                if(e->getAbsolute() > timeSignature[nTs]->getAbsolute())
                {
                    cTs++;
                    nTs = nTs+1 >= timeSignature.size() ? -1 : nTs+1;
                }
            }

            //Set Tempo
            if(nSt>=0)
            {
                if(e->getAbsolute() > tempo[nSt]->getAbsolute())
                {
                    cSt++;
                    nSt = nSt+1 >= tempo.size() ? -1 : nSt+1;
                }
            }

            SetTempo *st = cSt >= 0 ? (SetTempo*)tempo[cSt] : new SetTempo();
            TimeSignature *ts = cTs >=0 ? (TimeSignature*)timeSignature[cTs] : new TimeSignature() ;

            int lastRt = j > 0 ? t->getEvents()[j-1]->getAbsoluteRt() : 0;

            e->generateRealTimes(this->getTickTimeUs(st,ts), lastRt);
        }
    }
}

TimeData MidiFile::getTimeData()
{
    TimeSignature* ts = nullptr;
    SetTempo *st = nullptr;

    std::vector<MidiEvent*> events = fileInfo->getEvents();
    for(unsigned int i=0;i<events.size();i++)
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

    if(ts == nullptr || st == nullptr)
        return d;


    d.usPerQuarter = st->getTempo();
    d.clock = ts->getClock();
    d.denominator = ts->getDenominator();
    d.numerator = ts->getNumerator();
    d.thirtySeconds = ts->getThirtySeconds();
    return d;
}

int MidiFile::getTickTimeUs(SetTempo* st, TimeSignature* ts)
{
    int usPerBeat = st->getTempo();
    int tickPerBeat = header->getDivisions() * ts->getNumerator() / ts->getDenominator();
    int usPerTick = (usPerBeat / tickPerBeat);
    return usPerTick;
}

int MidiFile::getTickTimeUs()
{
    //http://www.lastrayofhope.co.uk/2009/12/23/midi-delta-time-ticks-to-seconds/
    TimeData d = this->getTimeData();
    int usPerBeat = d.usPerQuarter == 0 ? 500000 : d.usPerQuarter;
    int tickPerBeat = header->getDivisions() * d.numerator / d.denominator;
    int usPerTick = (usPerBeat / tickPerBeat);
    return usPerTick;
}
