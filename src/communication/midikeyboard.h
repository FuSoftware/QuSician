#ifndef MIDIKEYBOARD_H
#define MIDIKEYBOARD_H

#include <QObject>

#include "midiinworker.h"
#include "rtmidi/RtMidi.h"
#include "model/music/note.h"

//http://hinton-instruments.co.uk/reference/downloads/reference/midi_note_a4.pdf

class MidiKeyboard : public QObject
{
    Q_OBJECT
public:
    MidiKeyboard(int port, QObject* parent = 0);
    MidiKeyboard(int port, int startNote, int endNote, QObject* parent = 0);
    int getStart();
    int getEnd();
    int getKeyCount();
    int getRelativeNote(MidiNote n);
    int getRelativeNote(Note* n);
    static int getMaxKeyCount();
    static int getMinKey();
    static int getMaxKey();

public slots:
    void start(int port);
    void start();
    void stop();

signals:
    void NotePressed(MidiNote n);
    void NoteReleased(MidiNote n);
    void NoteEvent(MidiNote n);

private:
    int startNote;
    int endNote;
    int port;

    MidiInWorker* worker;
};

#endif // MIDIKEYBOARD_H
