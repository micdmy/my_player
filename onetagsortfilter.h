#ifndef ONETAGSORTFILTER_H
#define ONETAGSORTFILTER_H
#include <QSortFilterProxyModel>
#include <QRegularExpression>
class OneTagSortFilter : public QSortFilterProxyModel
{
public:
    OneTagSortFilter(QObject * parent = 0);
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
private:
      bool checkfilter(int sourceRow, const QModelIndex &sourceParent) const;
      bool checkText(int column, int sourceRow, const QModelIndex &sourceParent, QRegExp * regex) const;
};

#endif // ONETAGSORTFILTER_H
