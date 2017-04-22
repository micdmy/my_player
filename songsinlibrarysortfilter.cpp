#include "songsinlibrarysortfilter.h"

SongsInLibrarySortFilter::SongsInLibrarySortFilter(QObject *parent)
    :QSortFilterProxyModel(parent)
{
    blockSelectionChanges =false;
    setSelectedColumnSign('[',']');
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
    }
    return header;
}

void SongsInLibrarySortFilter::setSelectedColumnSign(const QChar &prefix, const QChar &suffix)
{
    selectedColumnSign[0] = prefix;
    selectedColumnSign[1] = suffix;
}

bool SongsInLibrarySortFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
    return checkfilter(sourceRow, sourceParent)
            && checkANDExtraFilters(sourceRow, sourceParent);
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

bool SongsInLibrarySortFilter::checkANDExtraFilters(int sourceRow,const QModelIndex &sourceParent) const
{
    //All filters must match.
    for(QPair<int,QString> filter : extraFilters) {
        QString text = sourceModel()->data(sourceModel()->index(sourceRow, filter.first, sourceParent)).toString();
        if(text != filter.second) {
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

void SongsInLibrarySortFilter::setExtraFilter(const int columnNumber, const QString &pattern)
{

    extraFilters.append(QPair<int,QString>(columnNumber, pattern));
}

void SongsInLibrarySortFilter::clearExtraFilter()
{
    extraFilters.clear();
}
