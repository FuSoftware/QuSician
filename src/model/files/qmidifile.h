#ifndef QMIDIFILE_H
#define QMIDIFILE_H

#include "qmusicfile.h"
#include "parsing/midi/midifile.h"

class QMidiFile : public QMusicFile
{
public:
    QMidiFile(QFileInfo info);

    MidiFile *getMidi();

private:
    void load(QFileInfo info);
    MidiFile *midi;
};

#endif // QMIDIFILE_H
