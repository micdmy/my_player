#ifndef ONETAGTABLEMODEL_H
#define ONETAGTABLEMODEL_H
#include <QAbstractTableModel>

class OneTagTableModel : public QAbstractTableModel
{
public:
    OneTagTableModel(QObject *parent = 0);
    OneTagTableModel(const QStringList headerNames, QList<QStringList *> columnsData, QObject *parent = 0);
    void initTableWithData(const QStringList & headerNames, QList<QStringList *> columnsData);
    int rowCount(const QModelIndex &parent = QModelIndex()) const ;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
private:
    QStringList headerNames;
    QList<QStringList *> columnsData;
};

#endif // ONETAGTABLEMODEL_H
