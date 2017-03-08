#include "songsinlibrary.h"

SongsInLibrary::SongsInLibrary()
{

}

QList<SongInfo> & SongsInLibrary::getSongsList()
{
    return songsList;
}

void SongsInLibrary::addSongs(const QStringList &pathList)
{
    for(QString path : pathList) {
        songsList.append(SongInfo(path));
    }
}

void SongsInLibrary::setSongs(const QStringList &pathList)
{
    songsList.clear();
    addSongs(pathList);
}

/*
 * Reading from stream.
 */
QDataStream & operator>>(QDataStream &dStream,  SongsInLibrary & songsInLibrary)
{
    songsInLibrary.songsList.clear();

    dStream >> songsInLibrary.songsList;
    return dStream;
}

/*
 * Saving to stream.
 */
QDataStream & operator<<(QDataStream & dStream, const SongsInLibrary & songsInLibrary)
{
    dStream << songsInLibrary.songsList;
    return dStream;
}

