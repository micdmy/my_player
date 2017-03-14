#include "songstablemodel.h"

SongsTableModel::SongsTableModel(QObject *parent,QStringList * songsList):
QAbstractTableModel(parent),
songsList(songsList)
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


