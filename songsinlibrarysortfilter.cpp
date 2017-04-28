#include "songsinlibrarysortfilter.h"

SongsInLibrarySortFilter::SongsInLibrarySortFilter(QObject *parent)
    :QSortFilterProxyModel(parent)
{
    blockSelectionChanges =false;
    setSelectedColumnSign('[',']');
    columnNames.setData(SongInfo::getUsedTags());
}

void SongsInLibrarySortFilter::setSelectionModel(QItemSelectionModel *selectionModel)
{
    this->selectionModel = selectionModel;
    connect(selectionModel,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,SLOT(selectionChanged(QItemSelection,QItemSelection)));
}

QVariant SongsInLibrarySortFilter::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant header = sourceModel()->headerData(section, orientation, role);
    switch(role) {
    case Qt::DisplayRole : {
        if(orientation == Qt::Horizontal) { //rows
            header = isColumnSelected(section) ? selectedColumnSign[0] + header.toString() + selectedColumnSign[1] : header;
        }
    }
    case WholeHeader : {
        return header; //QStringList
    }
    case TagName : {
        return header;
    }

    }
    return header;
}

void SongsInLibrarySortFilter::setSourceModel(QAbstractItemModel *sourceModel)
{
    QSortFilterProxyModel::setSourceModel(sourceModel);

}

void SongsInLibrarySortFilter::setSelectedColumnSign(const QChar &prefix, const QChar &suffix)
{
    selectedColumnSign[0] = prefix;
    selectedColumnSign[1] = suffix;
}

bool SongsInLibrarySortFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    return checkfilter(sourceRow, sourceParent)
            && checkOneTagFilters(sourceRow, sourceParent);
}

bool SongsInLibrarySortFilter::checkText(int column, int sourceRow, const QModelIndex &sourceParent, QRegExp * regex) const
{
    static const QRegularExpression theRegex(QString("(the\\s)"),QRegularExpression::CaseInsensitiveOption);
    QString text = sourceModel()->data(sourceModel()->index(sourceRow, column, sourceParent)).toString();
    text.remove(theRegex);
    return text.contains(*regex);
}

bool SongsInLibrarySortFilter::checkfilter(int sourceRow, const QModelIndex &sourceParent) const
{
    QString pattern = filterRegExp().pattern();
    if(pattern.isEmpty()) {
        return true;
    } else {
        QRegExp regex;
        bool displayThisRow = false;
        /*
         * if pattern longer then 2 chars, searches in whole text,
         * otherwise matches only beginnig of the text
         */
        if(pattern.length() <= 2) {
            pattern.insert(0,"^");
        }
        regex.setPattern(pattern);
        regex.setCaseSensitivity(Qt::CaseInsensitive);
        if(selectedColumns.isEmpty()) { //no selection, search in all columns
            for(int i=0; i<columnCount();i++) {
                if(checkText(i, sourceRow, sourceParent, &regex)) {
                    displayThisRow = true;
                    break;
                }
            }
        } else {
            for(QModelIndex index : selectedColumns) { //search in selected columns
                if(checkText(index.column(), sourceRow, sourceParent, &regex)) {
                    displayThisRow = true;
                    break;
                }
            }
        }
        return displayThisRow;
    }
}

bool SongsInLibrarySortFilter::checkOneTagFilters(int sourceRow,const QModelIndex &sourceParent) const
{
    for(auto tagName : activeOneTagFilters.keys()) {

        bool valueMatched=false;
        for(QString tagValue : activeOneTagFilters.value(tagName)) {
            QModelIndex as = sourceModel()->index(sourceRow, columnNames.getIndex(tagName), sourceParent);
            QString cellValue = sourceModel()->data(as).toString();
            if(cellValue == tagValue) {
                valueMatched = true;
                break;
            }
        }
        if(!valueMatched) {
            return false;
        }
    }
    return true;

}

bool SongsInLibrarySortFilter::isColumnSelected(int section) const
{
    for(QModelIndex index : selectedColumns) {
        if(section == index.column()) {
            return true;
        }
    }
    return false;
}
void SongsInLibrarySortFilter::selectionChanged(const QItemSelection &, const QItemSelection &)
{
    if(!blockSelectionChanges) {
        selectedColumns = selectionModel->selectedColumns();
    }
    blockSelectionChanges =false;
}

void SongsInLibrarySortFilter::filterChanged(const QString &pattern)
{
    blockSelectionChanges = true;
    setFilterRegExp(pattern);

}

void SongsInLibrarySortFilter::addExtraFilter(const int columnNumber, const QString &pattern)
{

    //extraFilters.append(QPair<int,QString>(columnNumber, pattern));
}

void SongsInLibrarySortFilter::clearExtraFilter()
{
    //extraFilters.clear();
}

void SongsInLibrarySortFilter::oneTagFilterChanged(QString tag, QStringList &selectedTagValues)
{
    activeOneTagFilters.insert(tag, selectedTagValues);
    setFilterRegExp(filterRegExp());
}
