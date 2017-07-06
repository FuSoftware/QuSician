#include "partition.h"

Partition::Partition()
{

}

Partition::Partition(MidiTrack* track)
{
    this->notes = loadMidiTrack(track);
}

vector<Note*> *Partition::loadMidiTrack(MidiTrack* track)
{
    vector<MidiEvent*> events = track->getEvents();

    vector<Note*> *notes = new vector<Note*>();

    for(int i=0;i<events.size();i++)
    {
        if(events[i]->getType() == MidiEventType::NOTE_ON)
        {
            NoteOn* e = (NoteOn*)events[i];
            notes->push_back(new Note(e->getAbsolute(), e->getKey(), e->getVelocity()));
        }
        else if(events[i]->getType() == MidiEventType::NOTE_OFF)
        {
            NoteOff* e = (NoteOff*)events[i];

            Note* n = Note::getLastOpenKey(notes,e->getKey());

            if(n != 0)
                n->setNoteOff(e->getAbsolute(),e->getVelocity());
            else
                cout << "Found a note ending but not starting at index " << i << endl;
        }
        else if(events[i]->getType() == MidiEventType::END_OF_TRACK)
        {
            EndOfTrack* e = (EndOfTrack*)events[i];

            for(int i=0;i<notes->size();i++)
            {
                Note *n = (*notes)[i];

                if(n->getStop() == -1)
                {
                    n->setNoteOff(e->getAbsolute(),0);
                }
            }
        }
    }

    return notes;
}

vector<Note*> *Partition::getNotes()
{
    return this->notes;
}

void Partition::toCSV(std::string path, std::string delimiter)
{
    std::ofstream out(path);

    out << "Start Ticks" << delimiter << "Start ms" << delimiter << "Stop Ticks" << delimiter << "Stop ms" << delimiter << "Key" << std::endl;

    for(int i=0;i<this->notes->size();i++)
    {
        Note* n = (*notes)[i];
        out << n->getStartTicks() << delimiter << n->getStart() << delimiter << n->getStopTicks() << delimiter << n->getStop() << delimiter << n->getKey() << std::endl;
    }
    out.close();
}

void Partition::setTickTime(int usPerTick)
{
    for(int i=0;i<this->notes->size();i++)
    {
        Note* n = (*notes)[i];
        n->setTickTime(usPerTick);
    }
}


