#ifndef MIDIOUTWORKER_H
#define MIDIOUTWORKER_H

#include <QObject>
#include <QThread>
#include <vector>
#include "rtmidi/rtmidiutils.h"
#include "parsing/midi/events/events.h"

class MidiOutWorker : public QObject
{
    Q_OBJECT
public:
    MidiOutWorker(int port, QObject *parent = nullptr);
    ~MidiOutWorker();

signals:
    void finished();

public slots:
    void noteOn(MidiNote n);
    void noteOn(int key, int velocity);

    void noteOff(MidiNote n);
    void noteOff(int key, int velocity);

    void noteEvent(MidiNote n);
    void noteEvent(bool state, int key, int velocity);

    void midiEvent(MidiEvent* e);

    void process();
    void stop();

private:
    RtMidiOut *midiout;
    int port;
    bool run;
};

#endif // MIDIOUTWORKER_H
