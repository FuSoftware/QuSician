#ifndef QMUSICFILE_H
#define QMUSICFILE_H

#include <QVariant>
#include <QVector>
#include <string>

#include <QFileInfo>
#include <QDir>

enum QMusicFileType{
    MIDI = 0,
    MUSIC_XML,
    UNRECOGNIZED
};

enum QMusicFileInfo{
    TITLE = 0,
    FOLDER,
    FORMAT,
    COMPLETED,
    END
};

class QMusicFile
{
public:
    QMusicFile(QFileInfo info);
    QVector<QVariant> getData();

protected:
    virtual void load(QFileInfo info) = 0;

    QString title;
    QString folder;
    QString format;
    int completed;

    QMusicFileType type;
    QFileInfo info;
};

#endif // QMUSICFILE_H
