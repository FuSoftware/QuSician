#include "qmusiclistwidget.h"

QMusicListWidget::QMusicListWidget(QWidget *parent) : QTableWidget(parent)
{
    this->setColumnCount((int)QMusicFileInfo::END);
    connect(this,SIGNAL(cellClicked(int,int)), this, SLOT(musicSelected(int,int)));
}

void QMusicListWidget::addFile(QMusicFile* f)
{
    if(f == 0)
        return;

    QVector<QVariant> data = f->getData();

    this->insertRow(this->rowCount());
    int row = this->rowCount() -1;

    for(int i=0;i<QMusicFileInfo::END;i++)
    {
        QTableWidgetItem *item = new QTableWidgetItem(data[i].toString());
        this->setItem(row,i,item);
    }

    this->files.push_back(f);
}

void QMusicListWidget::addFiles(QVector<QMusicFile*> f)
{
    for(int i=0;i<f.size();i++)
    {
        addFile(f[i]);
    }
}

void QMusicListWidget::musicSelected(int row, int column)
{
    QMusicFile *f = this->files[row];
    emit playMidi(((QMidiFile*)f)->getMidi());
}
