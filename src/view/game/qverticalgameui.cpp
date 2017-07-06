#include "qverticalgameui.h"

QVerticalGameUi::QVerticalGameUi(QWidget *parent) : QGameUi(parent)
{

}

void QVerticalGameUi::refresh(int t)
{

}

void QVerticalGameUi::paintEvent(QPaintEvent *event)
{
    this->painter = new QPainter(this);



    delete this->painter;
}

void QVerticalGameUi::drawBackground()
{

}

void QVerticalGameUi::drawNotes(QVector<Note*> notes)
{
    for(int i=0;i<notes.size();i++)
    {
        drawNote(notes[i]);
    }
}

void QVerticalGameUi::drawNote(Note* n)
{

}

void QVerticalGameUi::drawKeyboard()
{

}
