#include "onetagtablemodel.h"

OneTagTableModel::OneTagTableModel(QObject *parent):
QAbstractTableModel(parent)
{

}

OneTagTableModel::OneTagTableModel(const QStringList headerNames, QList<QStringList *> columnsData, QObject *parent):
QAbstractTableModel(parent),
headerNames(headerNames),
columnsData(columnsData)
{

}

void OneTagTableModel::initTableWithData(const QStringList &headerNames, QList<QStringList *> columnsData)
{
    this->headerNames = headerNames;
    this->columnsData = columnsData;
}

int OneTagTableModel::rowCount(const QModelIndex &/*parent*/) const
{ 
    if(!columnsData.isEmpty()) {
        return columnsData.first()->length();
    } else {
        return 0;
    }
}

int OneTagTableModel::columnCount(const QModelIndex &/*parent*/) const
{
    return columnsData.length();
}

QVariant OneTagTableModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
    case Qt::DisplayRole : {
        return columnsData.at(index.column()) ->at(index.row());
    }
    default : {
        return QVariant();
    }
    }
}

QVariant OneTagTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    switch(role) {
    case Qt::DisplayRole : {
        if(orientation == Qt::Vertical) { //rows
            return section;
        } else { //columns
            return headerNames.at(section);
        }
    }
    default : {
        return QVariant();
    }
    }
}
