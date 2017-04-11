#include "songsinlibrary.h"

SongsInLibrary::SongsInLibrary(QObject *parent):
QAbstractTableModel(parent)
{
}

QList<SongInfo> & SongsInLibrary::getSongsList()
{
    return songsList;
}

void SongsInLibrary::removeAllSongs()
{
    beginRemoveRows(QModelIndex(),0,rowCount()-1);
    songsList.clear();
    endRemoveRows();
}

void SongsInLibrary::addSongs(const QStringList &pathList)
{
    beginInsertRows(QModelIndex(), songsList.length(), songsList.length() + pathList.length() - 1);
    for(QString path : pathList) {
        songsList.append(SongInfo(path));
    }
    endInsertRows();
}

void SongsInLibrary::setColumns(const QStringList & tags)
{
    int before = columnCount();
    int after = tags.length()+1; // plus Path column, which is not included in tags
    int diff = after - before;
    if(diff > 0) { //add columns
        beginInsertColumns(QModelIndex(), before, before + diff - 1);
        SongInfo::setUsedTags(tags);
        endInsertColumns();
    } else if(diff < 0) { //remove columns
        beginRemoveColumns(QModelIndex(),before + diff, before - 1);
        SongInfo::setUsedTags(tags);
        endRemoveColumns();
    }
}

void SongsInLibrary::emitAllDataChanged()
{
    emit dataChanged(createIndex(0,0),createIndex(songsList.length(),SongInfo::getUsedTagsCount()));
}

void SongsInLibrary::findAllValuesOfTag(QString &tag, QStringList *foundValues)
{
    QSet<QString> set;
    for(SongInfo song : songsList) {
        set.insert(song.getMetadata(tag));
    }
    *foundValues = set.toList();
}

int SongsInLibrary::rowCount(const QModelIndex &/*parent*/) const
{
    return songsList.length();
}

int SongsInLibrary::columnCount(const QModelIndex &/*parent*/) const
{
    return SongInfo::getUsedTagsCount();
}

QVariant SongsInLibrary::data(const QModelIndex &index, int role) const
{
    switch(role) {
    case Qt::DisplayRole : {
        return (const_cast<SongInfo &>(songsList.at(index.row()))) .getMetadata(index.column());
    }
    default : {
        return QVariant();
    }
    }
}

QVariant SongsInLibrary::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role) {
    case Qt::DisplayRole : {
        if(orientation == Qt::Vertical) { //rows
            return section;
        } else { //columns
            return SongInfo::getUsedTag(section);
        }
    }
    default : {
        return QVariant();
    }
    }
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

