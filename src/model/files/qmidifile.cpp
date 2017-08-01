#include "qmidifile.h"

QMidiFile::QMidiFile(QFileInfo info) : QMusicFile(info), MidiFile(info.absoluteFilePath().toStdString())
{
    this->load(info);
}

void QMidiFile::load(QFileInfo info)
{
    this->type = QMusicFileType::MIDI;

    //Setup Data
    this->format = "MIDI";
    this->folder = info.absoluteDir().dirName();
    this->title = info.baseName();
    this->completed = -1;
}
