#ifndef QMIDIPORTSELECTION_H
#define QMIDIPORTSELECTION_H

#include <QtWidgets>
#include "rtmidi/RtMidi.h"
#include "qmidiportlist.h"

class QMidiPortSelection : public QWidget
{
    Q_OBJECT
public:
    QMidiPortSelection(QWidget *parent = nullptr);
    void loadUI();

signals:
    void inputSelected(int port);
    void outputSelected(int port);

public slots:
    void refresh();

private:
    QMidiPortList *lInputs;
    QMidiPortList *lOutputs;
};

#endif // QMIDIPORTSELECTION_H
