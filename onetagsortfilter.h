#ifndef ONETAGSORTFILTER_H
#define ONETAGSORTFILTER_H
#include <QSortFilterProxyModel>
#include <QRegularExpression>
#include <QItemSelection>
#include "onetagtablemodel.h"
class OneTagSortFilter : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    OneTagSortFilter(QObject * parent = 0);
    virtual ~OneTagSortFilter();
    void setSelectionModel(QItemSelectionModel * selectionModel);
protected:
    bool filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const override;
private:
    QItemSelectionModel * selectionModel;
    QStringList selectedTagValues;
    bool checkfilter(int sourceRow, const QModelIndex &sourceParent) const;
    bool checkText(int column, int sourceRow, const QModelIndex &sourceParent, QRegExp * regex) const;
signals:
    void oneTagFilterChanged(QstringList & selectedTagValues);
public slots:
    void selectionChanged(const QItemSelection & , const QItemSelection & );
};

#endif // ONETAGSORTFILTER_H
