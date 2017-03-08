#include "directorieslistmodel.h"

DirectoriesListModel::DirectoriesListModel(QObject *parent):
    QAbstractListModel(parent)
{

}

DirectoriesListModel::~DirectoriesListModel()
{

}


/*void DirectoriesListModel::setDirectory(int index, QString value)
{
    setData(createIndex(index,0),value);
}*/

int DirectoriesListModel::rowCount(const QModelIndex & /*parent*/) const
{
    return stringList.length();
}

QVariant DirectoriesListModel::data(const QModelIndex &index, int role) const
{
    switch(role) {
    case Qt::DisplayRole : {
        return stringList.at(index.row());
    }
    default : {
        return QVariant();
    }
    }

}

bool DirectoriesListModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    switch(role) {
    case Qt::EditRole : {
        QString path = value.toString();
        int i = index.row();
        if(i < stringList.length()) {
            stringList[i] = path;
            emit dataChanged(index,index);
        } else {
            ErrGui::error("DirectoriesListModel::setData(), index out of range");
        }
        break;
    }
    default : {
        break;
    }
    }
     return true;
}

QString DirectoriesListModel::add()
{
    QString path = getDirectoryPath();
    if(!path.isEmpty()) {
        stringList.append(path);
        emitDataChanded(stringList.length()-1);   
    }
    return path;
}

void DirectoriesListModel::remove(const unsigned int index)
{
    if((int)index < stringList.length()) {
        stringList.removeAt(index);
        emitDataChanded(index);
    } else {
        ErrGui::error("DirectoriesListModel::remove(), index out of range");
    }
}

QString DirectoriesListModel::edit(const unsigned int index)
{
    if((int)index < stringList.length()) {
        QString path = getDirectoryPath();
        if(!path.isEmpty()) {
            setData(createIndex(index,0),path);
            return path;
        }
    } else {
        ErrGui::error("DirectoriesListModel::edit(), index out of range");
    }
    return QString();
}

QStringList & DirectoriesListModel::getList()
{
    return stringList;
}

/*
 * reading from stream
 */
QDataStream & operator>>(QDataStream &dStream,  DirectoriesListModel &directoriesListModel)
{
    directoriesListModel.stringList.clear();
    dStream >> directoriesListModel.stringList;
    return dStream;
}
/*
 * saving to stream
 */
QDataStream & operator<<(QDataStream & dStream, const DirectoriesListModel &directoriesListModel)
{
    dStream << directoriesListModel.stringList;
    return dStream;
}

QString DirectoriesListModel::getDirectoryPath()
{
    QString dPath;
    dPath = QFileDialog::getExistingDirectory(nullptr,
                                             "Select folder with new media to add to library");
    return dPath;
}

void DirectoriesListModel::emitDataChanded(const unsigned int first)
{
    int l = stringList.length();
    QModelIndex lastItemIndex;
    if(l > 0) {
        lastItemIndex = createIndex(l-1,0);
    } else {
        lastItemIndex = createIndex(0,0);
    }

    if((int)first < l) {
        emit dataChanged(createIndex(first,0),lastItemIndex);
    } else {
        //bad first parameter, update all
        emit dataChanged(createIndex(0,0),lastItemIndex);
    }
}

