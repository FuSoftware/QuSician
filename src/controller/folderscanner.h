#ifndef FOLDERSCANNER_H
#define FOLDERSCANNER_H

#include <QObject>
#include <QStringList>
#include <QVariantList>
#include <QVector>
#include <QFileInfo>
#include <QDir>

#include "model/files/qmidifile.h"
#include "model/files/qmusicfile.h"

class FolderScanner : public QObject
{
    Q_OBJECT
public:
    FolderScanner(QStringList folders, QObject *parent = nullptr);

signals:
    void fileLoaded(QMusicFile* file);
    void filesLoaded(QVector<QMusicFile*> file);
    void finished();

public slots:
    void process();

private:
    QMusicFile* loadFile(QFileInfo fileInfo);
    QStringList folders;

};

#endif // FOLDERSCANNER_H
