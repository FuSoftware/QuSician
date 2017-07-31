#include "mainwindow.h"
#include <QApplication>

#include "tests.h"

int main(int argc, char *argv[])
{
    //Registering types
    qRegisterMetaType<MidiNote>("MidiNote");
    qRegisterMetaType<MidiEvent*>("MidiEvent*");

    //Application
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    TestMidiFile("D:\\Partitions\\Weimtime\\Highlight\\Youll Play Your Part - WeimTeam.mid");
    //KeyboardConfTest();
    //TestMidiPlayer();
    //PartitionToCSV("D:\\Prog\\MidiMusicXML\\MIDI_sample_synthesia.mid","D:\\Prog\\MidiMusicXML\\MIDI_sample_synthesia.csv",";");

    return a.exec();
}
