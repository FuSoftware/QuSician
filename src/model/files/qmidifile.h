#ifndef QMIDIFILE_H
#define QMIDIFILE_H

#include "qmusicfile.h"
#include "parsing/midi/midifile.h"

class QMidiFile : public QMusicFile, public MidiFile
{
public:
    QMidiFile(QFileInfo info);

private:
    void load(QFileInfo info);
};

#endif // QMIDIFILE_H
