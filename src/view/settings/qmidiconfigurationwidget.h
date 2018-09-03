#ifndef QMIDICONFIGURATIONWIDGET_H
#define QMIDICONFIGURATIONWIDGET_H

#include <QtWidgets>

class MidiOutput;
class MidiPlayer;
class QKeyboardWidget;
class QMidiPortSelection;
class Partition;

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
