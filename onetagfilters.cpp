#include "onetagfilters.h"

OneTagFilters::OneTagFilters(SongsInLibrary * songsInLibrary) :
   SortedTagValues(songsInLibrary)
{

}

OneTagFilters::~OneTagFilters()
{
    clear();
}

QList<OneTagSortFilter *> OneTagFilters::refresh(QStringList &tagNames)
{
    clear();
    SortedTagValues::refresh(tagNames);
    for(auto tagName : filters.keys()) {
        QStringList headerNames;
        QList<QStringList *> columnsData;
        headerNames.append(tagName);
        columnsData.append(filters.value(tagName));
        OneTagTableModel * oneTagTableModel
                = new OneTagTableModel(headerNames,columnsData);
        oneTagTableModels.append(oneTagTableModel);
        OneTagSortFilter * oneTagSortFilter
                = new OneTagSortFilter();
        oneTagSortFilter->setSourceModel(oneTagTableModel);
        oneTagSortFilters.append((oneTagSortFilter));
    }
    return oneTagSortFilters;
}

void OneTagFilters::clear()
{
    for(OneTagSortFilter * filter : oneTagSortFilters) {
        delete filter;
    }
    for(OneTagTableModel * model : oneTagTableModels) {
        delete model;
    }
    oneTagSortFilters.clear();
    oneTagTableModels.clear();
    SortedTagValues::clear();
}
