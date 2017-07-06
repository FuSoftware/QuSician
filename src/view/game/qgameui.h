#ifndef QGAMEUI_H
#define QGAMEUI_H

#include <QtWidgets>
#include <QVector>
#include "model/music/partition.h"

class QGameUi : public QWidget
{
    Q_OBJECT
public:
    QGameUi(QWidget *parent = nullptr);
    virtual void refresh(int t) = 0;

signals:

public slots:

protected:
    virtual void paintEvent(QPaintEvent *event) = 0;
    virtual void drawBackground() = 0;
    virtual void drawNotes(QVector<Note*> notes) = 0;
    virtual void drawNote(Note* n) = 0;
    virtual void drawKeyboard() = 0;

    int tStart;
    int tStop;
    int tCurrent;

    QVector<Partition*> partitions;
    QPainter *painter;

};

#endif // QGAMEUI_H
