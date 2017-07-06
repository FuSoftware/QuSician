#include "midiplayer.h"

MidiPlayer::MidiPlayer(Partition *p, QObject *parent) : QObject(parent)
{
    setPartition(p);
}

MidiPlayer::MidiPlayer(Partition *p, MidiOutput *out, QObject *parent) : QObject(parent)
{
    setPartition(p);
    setOutput(out);
}

void MidiPlayer::setOutput(MidiOutput *out)
{
    this->midiout = out;
    connect(this,SIGNAL(noteOn(MidiNote)),this->midiout,SLOT(noteOn(MidiNote)));
    connect(this,SIGNAL(noteOff(MidiNote)),this->midiout,SLOT(noteOff(MidiNote)));
    connect(this,SIGNAL(midiEvent(MidiEvent*)),this->midiout,SLOT(midiEvent(MidiEvent*)));
}

void MidiPlayer::setPartition(Partition *p)
{
    vector<Note*> notes = (*p->getNotes());
    this->noteEvents.clear();

    for(int i=0;i<notes.size();i++)
    {
        this->noteEvents.enqueue(RtMidiUtils::noteToMidi(true,notes[i]));
        this->noteEvents.enqueue(RtMidiUtils::noteToMidi(false,notes[i]));
    }

    std::sort(this->noteEvents.begin(),this->noteEvents.end(),midiNoteComp);
}

void MidiPlayer::setEvents(QVector<MidiEvent *> events)
{
    for(int i=0;i<events.size();i++)
    {
        if(!events[i]->isMetaEvent())
            this->midiEvents.enqueue(events[i]);
    }
}

void MidiPlayer::process()
{
    QTimer::singleShot(1,Qt::PreciseTimer,this,SLOT(nextEvent()));
}

void MidiPlayer::nextEvent()
{
    /*
    MidiNote m = this->noteEvents.head();
    emit noteEvent(m);
    if(m.state)
        emit noteOn(m);
    else
        emit noteOff(m);

    int elapsed = m.stamp;
    this->noteEvents.dequeue();

    QTimer::singleShot(this->noteEvents.head().stamp - elapsed,Qt::PreciseTimer,this,SLOT(nextEvent()));

    string type = m.state ? std::string("Start") : std::string("Stop ");
    std::cout << "Event " << type << ", stamp " << m.stamp << " | " << elapsed << " | " << elapsed - m.stamp << endl;
    */

    MidiEvent *e = this->midiEvents.dequeue();
    emit midiEvent(e);
    QTimer::singleShot(this->midiEvents.head()->getDeltaRt(),Qt::PreciseTimer,this,SLOT(nextEvent()));

}

void MidiPlayer::stop()
{
    run = false;
}
