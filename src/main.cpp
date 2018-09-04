#include "mainwindow.h"
#include <QApplication>

#include "tests.h"

#include "model/files/qmusicfile.h"

int main(int argc, char *argv[])
{
    //Registering types
    qRegisterMetaType<MidiNote>("MidiNote");
    qRegisterMetaType<MidiEvent*>("MidiEvent*");
    qRegisterMetaType<QMusicFile*>("QMusicFile*");
    qRegisterMetaType<MidiFile*>("MidiFile*");

    //Application
    QApplication a(argc, argv);
    //MainWindow w;
    //w.show();

    //TestRtMidi();

    //TestMidiFile("D:\\Partitions\\Weimtime\\QuSician\\Youll Play Your Part - WeimTeam.mid");
    //KeyboardConfTest();
    //TestMidiPlayer("D:\\Partitions\\Weimtime\\QuSician\\Youll Play Your Part - WeimTeam.mid");

    TestMusicList((QStringList() << "D:\\Partitions\\Weimtime\\QuSician\\" << "D:\\Partitions\\Weimtime\\Season 2\\"), 0);

    //Laptop
    //TestMusicList((QStringList() << "E:\\Partitions\\" << "E:\\Partitions\\Weimtime\\Season 3\\"), 0);
    //TestMusicList((QStringList() << "E:\\Partitions\\Weimtime\\QuSician\\"), 1);
    //TestMusicList((QStringList() << "~/Partitions/"), 1);

    return a.exec();
}
