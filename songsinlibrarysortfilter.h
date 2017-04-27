#ifndef SONGSINLIBRARYSORTFILTER_H
#define SONGSINLIBRARYSORTFILTER_H
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <QItemSelection>
#include <QHeaderView>
#include <QHash>
class SongsInLibrarySortFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    SongsInLibrarySortFilter(QObject * parent = 0);
    void setSelectionModel(QItemSelectionModel * selectionModel);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
    void setSelectedColumnSign(const QChar & prefix, const QChar & suffix);
    /*QDate getMinimumDate() const { return minDate; }
    void setFilterMinimumDate(const QDate &date);
    QDate getMaximumDate() const { return maxDate; }
    void setFilterMaximumDate(const QDate &date);*/

protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;

    // bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;
private:
   // bool dateInRange(const QDate &date) const;
    QModelIndexList selectedColumns;
    QItemSelectionModel * selectionModel;
    QChar selectedColumnSign[2];
    bool blockSelectionChanges;
    QList<QPair<int, QString>> extraFilters;
    bool checkfilter(int sourceRow, const QModelIndex &sourceParent) const;
    bool checkText(int column, int sourceRow, const QModelIndex &sourceParent, QRegExp * regex) const;
    bool checkANDExtraFilters(int sourceRow, const QModelIndex &sourceParent) const;
    bool isColumnSelected(int section) const;
public slots:
    void selectionChanged(const QItemSelection & , const QItemSelection & );
    void filterChanged(const QString & pattern);
    void addExtraFilter(const int columnNumber, const QString & pattern);
    void clearExtraFilter(void);
    /*
    QDate minDate;
    QDate maxDate;*/
};

#endif // SONGSINLIBRARYSORTFILTER_H
