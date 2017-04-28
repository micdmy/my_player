#ifndef SONGSINLIBRARYSORTFILTER_H
#define SONGSINLIBRARYSORTFILTER_H
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <QItemSelection>
#include <QHeaderView>
#include <QHash>
#include "columnnames.h"
#include "songinfo.h"
class SongsInLibrarySortFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    SongsInLibrarySortFilter(QObject * parent = 0);
    void setSelectionModel(QItemSelectionModel * selectionModel);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void setSourceModel(QAbstractItemModel *sourceModel);
    void setSelectedColumnSign(const QChar & prefix, const QChar & suffix);
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
private:
    enum displayRole{
        WholeHeader  = Qt::UserRole + 1,
        TagName
    };
    QModelIndexList selectedColumns;
    QItemSelectionModel * selectionModel;
    QChar selectedColumnSign[2];
    bool blockSelectionChanges;
    ColumnNames columnNames;
    QHash<QString, QStringList> activeOneTagFilters;
    bool checkfilter(int sourceRow, const QModelIndex &sourceParent) const;
    bool checkText(int column, int sourceRow, const QModelIndex &sourceParent, QRegExp * regex) const;
    bool checkOneTagFilters(int sourceRow, const QModelIndex &sourceParent) const;
    bool isColumnSelected(int section) const;
public slots:
    void selectionChanged(const QItemSelection & , const QItemSelection & );
    void filterChanged(const QString & pattern);
    void addExtraFilter(const int columnNumber, const QString & pattern);
    void clearExtraFilter(void);
    void oneTagFilterChanged(QString tag, QStringList & selectedTagValues);
};

#endif // SONGSINLIBRARYSORTFILTER_H
