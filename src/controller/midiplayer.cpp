#include "midiplayer.h"

MidiPlayer::MidiPlayer(QVector<MidiEvent *> events , MidiOutput *out, QObject *parent) : QObject(parent)
{
    addEventList(events);
    setOutput(out);
    init();
}

MidiPlayer::MidiPlayer(MidiOutput *out, QObject *parent) : QObject(parent)
{
    setOutput(out);
    init();
}

void MidiPlayer::setOutput(MidiOutput *out)
{
    this->midiout = out;

    if(this->midiout != 0)
        connect(this,SIGNAL(midiEvent(MidiEvent*)),this->midiout,SLOT(midiEvent(MidiEvent*)));
}

void MidiPlayer::addEventList(QVector<MidiEvent *> events)
{
    this->events.push_back(events);
}

void MidiPlayer::addTracks(QVector<MidiTrack*> tracks)
{
    for(int i=0;i<tracks.size();i++)
    {
        this->addTrack(tracks[i]);
    }
}

void MidiPlayer::addTrack(MidiTrack* track)
{
    this->addEventList(QVector<MidiEvent*>::fromStdVector(track->getChannelEvents()));
}

void MidiPlayer::init()
{
    for(int i=0;i<100;i++)
    {
        this->deltas.enqueue(0);
    }
    this->processTimer = new QTimer(this);
    this->processTimer->setSingleShot(true);
    this->processTimer->setInterval(1);
    connect(processTimer, SIGNAL(timeout()), this, SLOT(update()));
    this->last = 0;
}

void MidiPlayer::start()
{
    if(this->pauseTime >= 0)
    {
        setTime(this->pauseTime);
    }
    else
    {
        this->timer.start();
    }

    processTimer->start();
    this->pauseTime = -1;
    this->run = true;
}

void MidiPlayer::update()
{
    int current = this->timer.elapsed();
    int delta = current - this->last;

    //For each track
    for(int i=0;i<this->events.size();i++)
    {
        for(int j=0;j<this->events[i].size();j++)
        {
            MidiEvent *e = this->events[i][j];

            if(e->getAbsoluteRt() > current)
                break;

            if(e->getAbsoluteRt() > this->last && e->getAbsoluteRt() <=  current)
                emit midiEvent(e);
        }
    }

    this->deltas.dequeue();
    this->deltas.enqueue(delta);
    this->last = current;

    if(this->run)
        processTimer->start();
}

void MidiPlayer::stop()
{
    this->pauseTime = this->timer.elapsed();
    this->run = false;
}

void MidiPlayer::setTime(int ms)
{
    this->timer.restart();
    this->timer.addMSecs(ms);
}

void MidiPlayer::reset()
{
    this->timer.restart();
}

void MidiPlayer::restart()
{
    reset();
    start();
}

int MidiPlayer::getCurrentTime()
{
    return this->timer.elapsed();
}

int MidiPlayer::getMeanDelta()
{
    int mean = 0;

    for(int i=0;i<this->deltas.size();i++)
        mean += this->deltas[i];

    mean /= this->deltas.size();
    return mean;
}

void MidiPlayer::play(MidiFile* f)
{
    this->play(QVector<MidiTrack*>::fromStdVector(f->getTracks()));
}

void MidiPlayer::play(MidiFile* f, QVector<int> tracks)
{
    QVector<MidiTrack*> t;

    for(int i=0;i<tracks.size();i++)
    {
        t.push_back(f->getTracks()[tracks[i]]);
    }

    this->play(t);
}

void MidiPlayer::play(QVector<MidiTrack*> tracks)
{
    this->stop();
    this->events.clear();
    this->addTracks(tracks);
    this->restart();
}
