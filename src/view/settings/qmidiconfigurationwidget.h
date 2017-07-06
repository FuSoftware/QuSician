#ifndef QMIDICONFIGURATIONWIDGET_H
#define QMIDICONFIGURATIONWIDGET_H

#include <QtWidgets>

#include "qkeyboardwidget.h"
#include "qmidiportselection.h"
#include "communication/midioutput.h"
#include "controller/midiplayer.h"
#include "parsing/midi/midifile.h"

class QMidiConfigurationWidget : public QWidget
{
    Q_OBJECT
public:
    QMidiConfigurationWidget(QWidget *parent = nullptr);

signals:

public slots:
    void outputSelected(int port);
    void testAudio();

private:
    void initialize();
    QKeyboardWidget *keyboard;
    QMidiPortSelection *midiPorts;
    QPushButton *pbStartTest;

    MidiOutput *midiOutput;
    MidiPlayer *midiPlayer;

    Partition *partition;
};

#endif // QMIDICONFIGURATIONWIDGET_H
