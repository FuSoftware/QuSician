#ifndef MIDIOUTPUT_H
#define MIDIOUTPUT_H

#include <QObject>
#include "midioutworker.h"
#include "parsing/midi/events/events.h"

class MidiOutput : public QObject
{
    Q_OBJECT
public:
    MidiOutput(QObject *parent = nullptr);
    MidiOutput(int port, QObject *parent = nullptr);

signals:

public slots:
    void noteOn(MidiNote n);
    void noteOff(MidiNote n);
    void midiEvent(MidiEvent* e);

    void start(int port);
    void start();
    void stop();

private:
    int port;
    MidiOutWorker *worker;
};

#endif // MIDIOUTPUT_H
