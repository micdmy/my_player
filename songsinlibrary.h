#ifndef SONGSINLIBRARY_H
#define SONGSINLIBRARY_H

#include "songinfo.h"
#include <QList>

class SongsInLibrary
{
public:
    SongsInLibrary();
    QList<SongInfo> & getSongsList();
    void addSongs(const QStringList & pathList);
    void setSongs(const QStringList & pathList);
    //reading from QDataStream:
    friend QDataStream & operator>>(QDataStream & dStream, SongsInLibrary & songsInLibrary);
    //saving to QDataStream:
    friend QDataStream & operator<<(QDataStream & dStream,const SongsInLibrary & songsInLibrary);
private:
    QList<SongInfo> songsList;
};


#endif // SONGSINLIBRARY_H
