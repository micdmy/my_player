#ifndef SONGSINLIBRARYSORTFILTER_H
#define SONGSINLIBRARYSORTFILTER_H
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <QItemSelection>
#include <QHeaderView>
class SongsInLibrarySortFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    SongsInLibrarySortFilter(QObject * parent = 0);
    ~SongsInLibrarySortFilter();
    void setSelectionModel(QItemSelectionModel * selectionModel);
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
    bool checkText(int column, int sourceRow, const QModelIndex &sourceParent, QRegExp * regex) const;
    bool blockSelectionChanges;
public slots:
    void selectionChanged(const QItemSelection & , const QItemSelection & );
    void filterChanged(const QString & pattern);
    /*
    QDate minDate;
    QDate maxDate;*/
};

#endif // SONGSINLIBRARYSORTFILTER_H