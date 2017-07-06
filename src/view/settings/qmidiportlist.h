#ifndef QMIDIPORTLIST_H
#define QMIDIPORTLIST_H

#include <QtWidgets>
#include <QVector>

#include "rtmidi/rtmidiutils.h"

class QMidiPortList : public QWidget
{
    Q_OBJECT
public:
    QMidiPortList(QString title, QWidget *parent = nullptr);
    QMidiPortList(QString title, QVector<MidiPort> ports, QWidget *parent = nullptr);

    void initialize(QString title);

signals:
    void selected(int port);

public slots:
    void set(QVector<MidiPort> ports);
    void itemSelected(QListWidgetItem* item);

private:
    QListWidget *list;
    QLabel *label;
};

#endif // QMIDIPORTLIST_H
