#include "songstablemodel.h"

SongsTableModel::SongsTableModel(QObject *parent):
QAbstractTableModel(parent)
{

}

int SongsTableModel::rowCount(const QModelIndex &parent) const
{

}

int SongsTableModel::columnCount(const QModelIndex &parent) const
{

}

QVariant SongsTableModel::data(const QModelIndex &index, int role) const
{

}

/*
 * reading from stream
 */
QDataStream & operator>>(QDataStream &dStream,  SongsTableModel & songsTableModel)
{
    songsTableModel.songsList.clear();
    //dStream >> songsTableModel.songsList;

    return dStream;
}
/*
 * saving to stream
 */
QDataStream & operator<<(QDataStream & dStream, const SongsTableModel & songsTableModel)
{
    //dStream << songsTableModel.songsList;
    return dStream;
}
