#include "qmidifile.h"

#include "parsing/midi/midiparser.h"

QMidiFile::QMidiFile(QFileInfo info) : QMusicFile(info)
{
    this->load(info);
}

MidiFile *QMidiFile::getMidi()
{
    return this->midi;
}

void QMidiFile::load(QFileInfo info)
{
    this->type = QMusicFileType::MIDI;

    //Setup Data
    this->format = "MIDI";
    this->folder = info.absoluteDir().dirName();
    this->title = info.baseName();
    this->completed = -1;

    this->midi = MidiParser::parseFile(info.absoluteFilePath().toStdString());
}
