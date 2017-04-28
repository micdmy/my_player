#ifndef ONETAGFILTERS_H
#define ONETAGFILTERS_H
#include <QList>
#include "onetagtablemodel.h"
#include "onetagsortfilter.h"
#include "sortedtagvalues.h"
class OneTagFilters : public SortedTagValues
{
public:
    OneTagFilters(SongsInLibrary * songsInLibrary);
    ~OneTagFilters();
    QList<OneTagSortFilter *> refresh(QStringList &tagNames, QObject *receiver, const char *slot);
    void clear();
private:
    QList<OneTagTableModel *> oneTagTableModels;
    QList<OneTagSortFilter *> oneTagSortFilters;


};

#endif // ONETAGFILTERS_H
