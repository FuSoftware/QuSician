#ifndef TESTS_H
#define TESTS_H

#include <iostream>

#include "parsing/midi/midifile.h"
#include "rtmidi/RtMidi.h"
#include "view/settings/qmidiportselection.h"
#include "communication/midiinworker.h"
#include "model/music/partition.h"

#include "view/settings/qmidiconfigurationwidget.h"

#include "parsing/midi/variablelengthvalue.h"

#include <QVector>

void TestMidiFile(string file);
void TestRtMidi();
void TestMidiOutput();
void TestPortSelection();
void MidiWorkerTest();
void PartitionTestMidi();
void KeyboardConfTest();
void MidiInOutTest();
void PartitionToCSV(std::string file, string csv, string delimiter);

void TestVSV();
void TestMidiPlayer();

#endif // TESTS_H
