#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QThread>
#include <QVector>

#include "model/music/partition.h"
#include "rtmidi/rtmidiutils.h"
#include "communication/midioutput.h"
#include "parsing/midi/events/events.h"

class MidiPlayer : public QObject
{
    Q_OBJECT
public:
    MidiPlayer(Partition *p, QObject *parent = nullptr);
    MidiPlayer(Partition *p, MidiOutput *out, QObject *parent = nullptr);
    MidiPlayer(MidiOutput *out, QObject *parent = nullptr);
    void setOutput(MidiOutput *out);
    void setPartition(Partition *p);
    void setEvents(QVector<MidiEvent*> events);

signals:
    void finished();
    void noteOn(MidiNote n);
    void noteOff(MidiNote n);
    void noteEvent(MidiNote n);
    void midiEvent(MidiEvent* e);

public slots:
    void process();
    void stop();
    void nextEvent();

private:
    QQueue<MidiNote> noteEvents;
    QQueue<MidiEvent*> midiEvents;

    bool run;
    MidiOutput *midiout;
};

#endif // MIDIPLAYER_H
