#include "qmidiportlist.h"

QMidiPortList::QMidiPortList(QString title, QWidget *parent) : QWidget(parent)
{
    initialize(title);
}

QMidiPortList::QMidiPortList(QString title, QVector<MidiPort> ports, QWidget *parent) : QWidget(parent)
{ 
    initialize(title);
    set(ports);
}

void QMidiPortList::initialize(QString title)
{
    list = new QListWidget(this);
    label = new QLabel(title, this);

    QVBoxLayout *l = new QVBoxLayout;
    l->addWidget(label);
    l->addWidget(list);

    setLayout(l);
}

void QMidiPortList::set(QVector<MidiPort> ports)
{
    list->clear();
    for(int i=0;i<ports.size();i++)
    {
        QListWidgetItem *item = new QListWidgetItem(list);
        item->setText(QString::number(ports[i].id) + QString(" ") + QString(ports[i].name.c_str()));
        item->setData(1,i);
        list->addItem(item);
    }

    connect(list,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(itemSelected(QListWidgetItem*)));
}

void QMidiPortList::itemSelected(QListWidgetItem *item)
{
    int port = item->data(1).toInt();
    emit selected(port);
}
