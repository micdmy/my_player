#include "mediadirectories.h"

MediaDirectories::MediaDirectories(QObject *parent) : QObject(parent)
{

}

void MediaDirectories::add()
{
    directoriesPaths.append(getDirectoryPath());
}

void MediaDirectories::remove(QString seekPath)
{
    int index = directoriesPaths.indexOf(QRegExp(seekPath));
    if(index > 0) {
        directoriesPaths.removeAt(index);
    }
}

void MediaDirectories::removeAll()
{
    clearDirectoryPaths();
}

void MediaDirectories::edit(int index)
{
    QString * pathAtIndex = &(directoriesPaths[index]);
    *pathAtIndex = getDirectoryPath();
}

QStringList MediaDirectories::getList()
{
    return directoriesPaths;
}

/*
 * reading from stream
 */
QDataStream & operator>>(QDataStream &dStream,  MediaDirectories &mediaDirectories)
{
    mediaDirectories.clearDirectoryPaths();
    dStream >> mediaDirectories.directoriesPaths;
    return dStream;
}
/*
 * saving to stream
 */
QDataStream & operator<<(QDataStream & dStream, const MediaDirectories &mediaDirectories)
{
    dStream << mediaDirectories.directoriesPaths;
    return dStream;
}

QString MediaDirectories::getDirectoryPath()
{
    QString dPath;
    dPath = QFileDialog::getExistingDirectory(nullptr,
                                             "Select folder with new media to add to library");
    return dPath;
}
/*
 * PRIVATE FUNCTIONS:
 */
void MediaDirectories::clearDirectoryPaths()
{
    directoriesPaths.clear();
}

