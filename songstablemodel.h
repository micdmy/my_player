#ifndef SONGSTABLEMODEL_H
#define SONGSTABLEMODEL_H
#include <QAbstractTableModel>
#include <QMediaPlaylist>
#include <QMediaContent>
#include <QDataStream>

class SongsTableModel : public QAbstractTableModel
{
    Q_OBJECT
public:
    SongsTableModel(QObject *parent, QStringList * songsList);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

private:
    QStringList * songsList;
};

#endif // SONGSTABLEMODEL_H
