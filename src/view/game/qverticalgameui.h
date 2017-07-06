#ifndef QVERTICALGAMEUI_H
#define QVERTICALGAMEUI_H

#include "qgameui.h"


class QVerticalGameUi : public QGameUi
{
public:
    QVerticalGameUi(QWidget *parent = nullptr);
    void refresh(int t);

signals:

public slots:

protected:
    void paintEvent(QPaintEvent *event);

private:
    void drawBackground();
    void drawNotes(QVector<Note*> notes);
    void drawNote(Note* n);
    void drawKeyboard();
};

#endif // QVERTICALGAMEUI_H
