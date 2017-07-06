#ifndef MIDIINWORKER_H
#define MIDIINWORKER_H

#include <QObject>
#include <QThread>
#include <vector>
#include "rtmidi/rtmidiutils.h"

using namespace std;

class MidiInWorker : public QObject
{
    Q_OBJECT
public:
    MidiInWorker(int port, QObject *parent = nullptr);
    ~MidiInWorker();

signals:
    void finished();
    void noteEvent(MidiNote n);
    void noteOn(MidiNote n);
    void noteOff(MidiNote n);

public slots:
    void process();
    void stop();

private:
    int port;
    void eventReceived(double deltatime, vector<unsigned char> *message, void *userData);
    RtMidiIn* midiin;
    bool run;
};

#endif // MIDIINWORKER_H
