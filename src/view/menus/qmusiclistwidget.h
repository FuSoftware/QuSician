#ifndef QMUSICLISTWIDGET_H
#define QMUSICLISTWIDGET_H

#include <QtWidgets>
#include <QVector>

#include "model/files/qmidifile.h"
#include "model/files/qmusicfile.h"

class QMusicListWidget : public QTableWidget
{
    Q_OBJECT
public:
    QMusicListWidget(QWidget *parent = nullptr);

signals:
    void playMidi(MidiFile* f);

public slots:
    void addFile(QMusicFile* f);
    void addFiles(QVector<QMusicFile*> f);
    void musicSelected(int row, int column);

private:
    QVector<QMusicFile*> files;
};

#endif // QMUSICLISTWIDGET_H
