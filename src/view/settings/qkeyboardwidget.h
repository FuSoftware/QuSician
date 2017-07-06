#ifndef QKEYBOARDCONFIGURATION_H
#define QKEYBOARDCONFIGURATION_H

#include "communication/midikeyboard.h"

#include <QtWidgets>

class QKeyboardWidget : public QWidget
{
    Q_OBJECT
public:
    QKeyboardWidget(QWidget *parent = nullptr);
    ~QKeyboardWidget();

public slots:
    void setPort(int port);
    void notePressed(MidiNote n);

protected:
    void paintEvent(QPaintEvent *event);

private:
    void drawKeyboard(MidiKeyboard *k);
    void drawKey(int index, bool sharp, bool selected);

    int keyLength;

    QPainter *painter;
    MidiKeyboard *keyboard;

    int minKey;
    int maxKey;
    bool keyToSave;

};

#endif // QKEYBOARDCONFIGURATION_H
