#ifndef QTESTGAMEUI_H
#define QTESTGAMEUI_H

#include "qgameui.h"

class QTestGameUi : public QGameUi
{
    Q_OBJECT
public:
    QTestGameUi(QWidget *parent = nullptr);

private:
    void paintEvent(QPaintEvent *event);
    void drawBackground();
    void drawNotes(QVector<Note*> notes);
    void drawNote(Note* n);
    void drawKeyboard();

    int getMaxVisibleDelta();
    int getMinVisibleDelta();
    void setVisibleLength(int measures);

};

#endif // QTESTGAMEUI_H
