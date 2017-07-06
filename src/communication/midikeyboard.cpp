#include "midikeyboard.h"

MidiKeyboard::MidiKeyboard(int port, int startNote, int endNote, QObject *parent) : QObject(parent)
{
    this->port = port;
    this->startNote = startNote;
    this->endNote = endNote;
    this->worker = 0;
}

void MidiKeyboard::start(int port)
{
    if(this->worker != 0)
    {
        stop();
    }

    QThread *t = new QThread();
    this->worker = new MidiInWorker(port);

    connect(t, SIGNAL(started()),  this->worker, SLOT(process()));
    connect(this->worker, SIGNAL(finished()), t, SLOT(quit()));
    connect(this->worker, SIGNAL(finished()), this->worker, SLOT(deleteLater()));
    connect(t, SIGNAL(finished()), t, SLOT(deleteLater()));

    connect(this->worker,SIGNAL(noteOn(MidiNote)),this,SIGNAL(NotePressed(MidiNote)));
    connect(this->worker,SIGNAL(noteOff(MidiNote)),this,SIGNAL(NoteReleased(MidiNote)));
    connect(this->worker,SIGNAL(noteEvent(MidiNote)),this,SIGNAL(NoteEvent(MidiNote)));

    this->worker->moveToThread(t);
    t->start();
}

void MidiKeyboard::start()
{
    start(this->port);
}

void MidiKeyboard::stop()
{
    worker->stop();
}

int MidiKeyboard::getMaxKeyCount()
{
    return getMaxKey() - getMinKey();
}

int MidiKeyboard::getMinKey()
{
    return 0;
}

int MidiKeyboard::getMaxKey()
{
    return 127;
}

int MidiKeyboard::getKeyCount()
{
    return this->getEnd() - this->getStart();
}

int MidiKeyboard::getEnd()
{
    return this->endNote;
}

int MidiKeyboard::getStart()
{
    return this->startNote;
}

int MidiKeyboard::getRelativeNote(MidiNote n)
{
    return n.key - this->startNote;
}

int MidiKeyboard::getRelativeNote(Note* n)
{
    return n->getKey() - this->startNote;
}
