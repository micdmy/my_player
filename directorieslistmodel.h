#ifndef DIRECTORIESLISTMODEL_H
#define DIRECTORIESLISTMODEL_H
#include <QStringListModel>
#include <QStringList>
#include <QFileDialog>
#include <QAbstractListModel>
#include "errgui.h"
class DirectoriesListModel : public QAbstractListModel
{
public:
    explicit DirectoriesListModel(QObject *parent = Q_NULLPTR);
    virtual ~DirectoriesListModel();
    int rowCount(const QModelIndex &parent = QModelIndex()) const override ;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex & index, const QVariant & value, int role = Qt::EditRole) override;


    QString add();
    void remove(const unsigned int index);
    QString edit(const unsigned int index);
    QStringList & getList();
    //reading from QDataStream:
    friend QDataStream & operator>>(QDataStream & dStream, DirectoriesListModel &directoriesListModel);
    //saving to QDataStream:
    friend QDataStream & operator<<(QDataStream & dStream,const DirectoriesListModel &directoriesListModel);
    QString getDirectoryPath();
    //void setDirectory(int index, QString value);
private:
    QStringList stringList;
    void emitDataChanded(const unsigned int first);
signals:
    void editCompleted(const QString &);
};

#endif // DIRECTORIESLISTMODEL_H
