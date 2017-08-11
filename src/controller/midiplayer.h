#ifndef MIDIPLAYER_H
#define MIDIPLAYER_H

#include <QObject>
#include <QQueue>
#include <QTimer>
#include <QThread>
#include <QVector>
#include <QTime>

#include "rtmidi/rtmidiutils.h"
#include "communication/midioutput.h"

#include "parsing/midi/events/events.h"
#include "parsing/midi/midifile.h"

class MidiPlayer : public QObject
{
    Q_OBJECT
public:
    MidiPlayer(QVector<MidiEvent*> events, MidiOutput *out = 0, QObject *parent = 0);
    MidiPlayer(MidiOutput *out = 0, QObject *parent = 0);
    void setOutput(MidiOutput *out);

    void clear();
    void addEventList(QVector<MidiEvent*> events);
    void addTracks(QVector<MidiTrack*> tracks);
    void addTrack(MidiTrack* track);

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
    void restart();
    void update();

    void play(MidiFile* f);
    void play(MidiFile* f, QVector<int> tracks);
    void play(QVector<MidiTrack*> tracks);

private:
    QVector<QVector<MidiEvent*>> events;

    bool run;
    MidiOutput *midiout;

    int pauseTime = -1;
    int last;
    QTime timer;
    QTimer *processTimer;

    QQueue<int> deltas;
};

#endif // MIDIPLAYER_H
