#ifndef QKEYBOARD_H
#define QKEYBOARD_H

#include <QtWidgets>
#include "parsing/midi/events/midievent.h"

#include <QVector>

class QKeyboard : public QWidget
{
    Q_OBJECT
public:
    QKeyboard(int start, int end, QWidget *parent = nullptr);

signals:

public slots:
    void keyEvent(MidiEvent* e);
    void pressKey(int k);
    void releaseKey(int k);
    
private:
    QVector<bool> keyStates;

};

#endif // QKEYBOARD_H
