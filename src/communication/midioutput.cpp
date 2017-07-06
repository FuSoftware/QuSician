#include "midioutput.h"

MidiOutput::MidiOutput(QObject *parent) : QObject(parent)
{
    this->worker = 0;
}

MidiOutput::MidiOutput(int port, QObject *parent) : QObject(parent)
{
    this->worker = 0;
    start(port);
}

void MidiOutput::noteOn(MidiNote n)
{
    worker->noteOn(n);
}

void MidiOutput::noteOff(MidiNote n)
{
    worker->noteOff(n);
}

void MidiOutput::midiEvent(MidiEvent* e)
{
    worker->midiEvent(e);
}

void MidiOutput::start(int port)
{
    this->port = port;

    if(this->worker != 0)
    {
        stop();
    }

    QThread *t = new QThread();
    this->worker = new MidiOutWorker(port);

    connect(t, SIGNAL(started()),  this->worker, SLOT(process()));
    connect(this->worker, SIGNAL(finished()), t, SLOT(quit()));
    connect(this->worker, SIGNAL(finished()), this->worker, SLOT(deleteLater()));
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

    this->worker->moveToThread(t);
    t->start();
}

void MidiOutput::start()
{
    start(this->port);
}

void MidiOutput::stop()
{
    worker->stop();
}
