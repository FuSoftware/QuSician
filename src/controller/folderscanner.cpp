#include "folderscanner.h"

FolderScanner::FolderScanner(QStringList folders, QObject *parent) : QObject(parent)
{
    this->folders = folders;
}

void FolderScanner::process()
{
    QStringList extensions;
    extensions << "*.mid";

    QVector<QMusicFile*> files;

    for(int i=0;i<this->folders.size();i++)
    {
        QDir d = QDir(this->folders[i]);
        d.setNameFilters(extensions);
        d.setFilter(QDir::Files | QDir::NoDotAndDotDot);

        for(int i=0;i<d.entryList().size();i++)
        {
            QMusicFile *f = loadFile(d.entryInfoList()[i]);
            files.push_back(f);
            emit fileLoaded(f);
        }
    }

    emit filesLoaded(files);
    emit finished();
}

QMusicFile *FolderScanner::loadFile(QFileInfo fileInfo)
{
    QString ext = fileInfo.completeSuffix();
    QMusicFile *f = 0;

    if(ext == "mid")
        f = new QMidiFile(fileInfo);


    return f;
}
