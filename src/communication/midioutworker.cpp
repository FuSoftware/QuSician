#include "midioutworker.h"

MidiOutWorker::MidiOutWorker(int port, QObject *parent) : QObject(parent)
{
    midiout = new RtMidiOut();
    this->port = port;
}

MidiOutWorker::~MidiOutWorker()
{
    delete midiout;
}

void MidiOutWorker::noteOn(MidiNote n)
{
    noteEvent(true, n.key, n.velocity);
}

void MidiOutWorker::noteOn(int key, int velocity)
{
    noteEvent(true,key,velocity);
}

void MidiOutWorker::noteOff(MidiNote n)
{
    noteEvent(false,n.key, n.velocity);
}

void MidiOutWorker::noteOff(int key, int velocity)
{
    noteEvent(false,key,velocity);
}

void MidiOutWorker::noteEvent(MidiNote n)
{
    noteEvent(n.state,n.key,n.velocity);
}

void MidiOutWorker::noteEvent(bool state, int key, int velocity)
{
    vector<unsigned char> message;
    message.push_back(state ? 0x90 : 0x80);
    message.push_back(key);
    message.push_back(velocity);

    midiout->sendMessage(&message);
}

void MidiOutWorker::midiEvent(MidiEvent* e)
{
    vector<unsigned char> message = e->getData();
    midiout->sendMessage(&message);
}

void MidiOutWorker::process()
{
    this->midiout->openPort(this->port);    
}

void MidiOutWorker::stop()
{
    this->midiout->closePort();
    emit finished();
}
