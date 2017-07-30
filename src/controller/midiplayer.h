#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QThread>
#include <QVector>
#include <QTime>

#include "model/music/partition.h"
#include "rtmidi/rtmidiutils.h"
#include "communication/midioutput.h"
#include "parsing/midi/events/events.h"

class MidiPlayer : public QObject
{
    Q_OBJECT
public:
    MidiPlayer(QVector<MidiEvent*> events, MidiOutput *out = nullptr, QObject *parent = nullptr);
    MidiPlayer(MidiOutput *out, QObject *parent = nullptr);
    void setOutput(MidiOutput *out);
    void addEventList(QVector<MidiEvent*> events);

    void init();
    void setTime(int ms);
    int getCurrentTime();

    int getMeanDelta();

signals:
    void finished();
    void midiEvent(MidiEvent* e);

public slots:
    void start();
    void stop();
    void reset();
    void update();

private:
    QVector<QVector<MidiEvent*>> events;
    QQueue<MidiEvent*> midiEvents;

    bool run;
    MidiOutput *midiout;

    int pauseTime = -1;
    int last;
    QTime timer;
    QTimer *processTimer;

    QQueue<int> deltas;
};

#endif // MIDIPLAYER_H
