#include "qmusicfile.h"

QMusicFile::QMusicFile(QFileInfo info)
{
    this->info = info;
}

QVector<QVariant> QMusicFile::getData()
{
    QVector<QVariant> list = QVector<QVariant>((int)QMusicFileInfo::END);
    list[QMusicFileInfo::TITLE] = this->title;
    list[QMusicFileInfo::FOLDER] = this->folder;
    list[QMusicFileInfo::FORMAT] = this->format;
    list[QMusicFileInfo::COMPLETED] = this->completed;
    return list;
}
