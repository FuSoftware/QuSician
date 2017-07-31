#-------------------------------------------------
#
# Project created by QtCreator 2017-07-02T21:47:30
#
#-------------------------------------------------

QT       += core gui
CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QuSician
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    parsing/midi/midifile.cpp \
    parsing/midi/midiheader.cpp \
    parsing/midi/events/midievent.cpp \
    tests.cpp \
    parsing/filereader.cpp \
    parsing/conversion.cpp \
    parsing/midi/miditrack.cpp \
    parsing/midi/events/channelvoiceevents/noteon.cpp \
    parsing/midi/events/channelvoiceevents/channelpressure.cpp \
    parsing/midi/events/channelvoiceevents/controlchange.cpp \
    parsing/midi/events/channelvoiceevents/noteoff.cpp \
    parsing/midi/events/channelvoiceevents/pitchwheelchange.cpp \
    parsing/midi/events/channelvoiceevents/polyphonickeypressure.cpp \
    parsing/midi/events/channelvoiceevents/programchange.cpp \
    parsing/midi/events/metaevents/endoftrack.cpp \
    parsing/midi/events/metaevents/midichannelprefix.cpp \
    parsing/midi/events/metaevents/sequencenumber.cpp \
    parsing/midi/events/metaevents/settempo.cpp \
    parsing/midi/events/metaevents/smpteoffset.cpp \
    parsing/midi/events/metaevents/textevent.cpp \
    parsing/midi/events/metaevents/timesignature.cpp \
    communication/midikeyboard.cpp \
    rtmidi/RtMidi.cpp \
    view/settings/qmidiportselection.cpp \
    rtmidi/RtMidiUtils.cpp \
    view/settings/qmidiportlist.cpp \
    communication/midiinworker.cpp \
    model/music/note.cpp \
    model/music/partition.cpp \
    view/game/qgameui.cpp \
    view/game/qverticalgameui.cpp \
    view/game/qkeyboard.cpp \
    view/settings/qkeyboardwidget.cpp \
    view/settings/qmidiconfigurationwidget.cpp \
    communication/midioutworker.cpp \
    communication/midioutput.cpp \
    controller/midiplayer.cpp \
    view/game/qhorizontalgameui.cpp \
    view/game/qtestgameui.cpp \
    parsing/midi/variablelengthvalue.cpp \
    parsing/midi/events/metaevents/keysignature.cpp \
    view/menus/qmusiclistwidget.cpp

HEADERS += \
        mainwindow.h \
    parsing/midi/midifile.h \
    parsing/midi/midiheader.h \
    parsing/midi/events/midievent.h \
    tests.h \
    parsing/filereader.h \
    parsing/conversion.h \
    parsing/midi/miditrack.h \
    parsing/midi/events/channelvoiceevents/noteon.h \
    parsing/midi/events/channelvoiceevents/channelpressure.h \
    parsing/midi/events/channelvoiceevents/controlchange.h \
    parsing/midi/events/channelvoiceevents/noteoff.h \
    parsing/midi/events/channelvoiceevents/pitchwheelchange.h \
    parsing/midi/events/channelvoiceevents/polyphonickeypressure.h \
    parsing/midi/events/channelvoiceevents/programchange.h \
    parsing/midi/events/events.h \
    parsing/midi/events/metaevents/endoftrack.h \
    parsing/midi/events/metaevents/midichannelprefix.h \
    parsing/midi/events/metaevents/sequencenumber.h \
    parsing/midi/events/metaevents/settempo.h \
    parsing/midi/events/metaevents/smpteoffset.h \
    parsing/midi/events/metaevents/textevent.h \
    parsing/midi/events/metaevents/timesignature.h \
    communication/midikeyboard.h \
    rtmidi/RtMidi.h \
    view/settings/qmidiportselection.h \
    rtmidi/RtMidiUtils.h \
    view/settings/qmidiportlist.h \
    communication/midiinworker.h \
    model/music/note.h \
    model/music/partition.h \
    view/game/qgameui.h \
    view/game/qverticalgameui.h \
    view/game/qkeyboard.h \
    view/settings/qkeyboardwidget.h \
    view/settings/qmidiconfigurationwidget.h \
    communication/midioutworker.h \
    communication/midioutput.h \
    controller/midiplayer.h \
    view/game/qhorizontalgameui.h \
    view/game/qtestgameui.h \
    parsing/midi/variablelengthvalue.h \
    parsing/midi/events/metaevents/keysignature.h \
    view/menus/qmusiclistwidget.h

#Refer to https://www.music.mcgill.ca/~gary/rtmidi/index.html#compiling

DEFINES += RTMIDI_DEBUG

win32 {
    DEFINES += __WINDOWS_MM__
    LIBS += -lwinmm
}

DISTFILES +=
