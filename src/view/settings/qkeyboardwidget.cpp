#include "qkeyboardwidget.h"

QKeyboardWidget::QKeyboardWidget(QWidget *parent) : QWidget(parent)
{
    this->minKey = 0;
    this->maxKey = 0;
    this->keyboard = 0;
    this->keyToSave = false;

    this->setMinimumHeight(75);
}

QKeyboardWidget::~QKeyboardWidget()
{
    this->keyboard->stop();
}

void QKeyboardWidget::setPort(int port)
{ 
    if(this->keyboard == 0)
    {
        this->keyboard = new MidiKeyboard(port,MidiKeyboard::getMinKey(), MidiKeyboard::getMaxKey(),this);
        this->keyboard->start();
        connect(this->keyboard,SIGNAL(NotePressed(MidiNote)),this,SLOT(notePressed(MidiNote)));
    }
    else
    {
        this->keyboard->stop();
        this->keyboard->start(port);
    }

    this->update();
}


void QKeyboardWidget::notePressed(MidiNote n)
{
    if(keyToSave)
        this->maxKey = n.key;
    else
        this->minKey = n.key;

    keyToSave = !keyToSave;
    this->update();
}

void QKeyboardWidget::paintEvent(QPaintEvent *event)
{
    painter = new QPainter(this);

    if(this->keyboard != 0)
    {
        drawKeyboard(this->keyboard);
    }

    delete painter;
}

void QKeyboardWidget::drawKeyboard(MidiKeyboard *k)
{
    this->keyLength = this->width() / k->getMaxKeyCount();

    QRect r = QRect(0,0,this->width(),this->height());
    QPen p = QColor(128,128,128);
    this->painter->setPen(p);
    this->painter->fillRect(r, QColor(128,128,128));

    for(int i=0;i<k->getMaxKeyCount();i++)
    {
        drawKey(i, RtMidiUtils::isSharp(i), (i >= this->minKey && i<= this->maxKey));
    }
}

void QKeyboardWidget::drawKey(int index, bool sharp, bool selected)
{
    int x = this->keyLength*index;
    int y = 0;
    int w = this->keyLength;
    int h = sharp ? this->height()*(1/2) : this->height();

    QRect r = QRect(x,y,w,h);
    QPen p = QColor(0,0,0);
    this->painter->setPen(p);

    if(selected)
    {
        if(sharp)
        {
            h = this->height()/2;
            this->painter->fillRect(x,y,w,h, QColor(0,0,0));
            this->painter->fillRect(x,y+(this->height()-h),w,h, QColor(255,255,255));
        }
        else
        {
            QRect r = QRect(x,y,w,h);
            this->painter->fillRect(r, QColor(255,255,255));
        }
    }
    else
    {
        this->painter->fillRect(r, QColor(128,128,128));
    }

}
