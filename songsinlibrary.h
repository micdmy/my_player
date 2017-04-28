#ifndef SONGSINLIBRARY_H
#define SONGSINLIBRARY_H

#include "songinfo.h"
#include <QList>
#include <QAbstractTableModel>

class SongsInLibrary : public QAbstractTableModel
{
public:
    enum displayRole{
        WholeHeader = Qt::UserRole + 1
    };
    SongsInLibrary(QObject * parent = 0);
    QList<SongInfo> & getSongsList();
    void removeAllSongs();
    void addSongs(const QStringList & pathList);
    void setColumns(const QStringList & tags);
    void emitAllDataChanged(void);
    void findAllValuesOfTag(QString &tag, QStringList *foundValues);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    //reading from QDataStream:
    friend QDataStream & operator>>(QDataStream & dStream, SongsInLibrary & songsInLibrary);
    //saving to QDataStream:
    friend QDataStream & operator<<(QDataStream & dStream,const SongsInLibrary & songsInLibrary);
private:
    QList<SongInfo> songsList;
    QModelIndexList lastSelectedColumns;
    bool isColumnSelected(int section) const;

};


#endif // SONGSINLIBRARY_H
