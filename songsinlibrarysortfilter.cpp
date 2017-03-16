#include "songsinlibrarysortfilter.h"

SongsInLibrarySortFilter::SongsInLibrarySortFilter(QObject *parent)
    :QSortFilterProxyModel(parent)
{
    blockSelectionChanges =false;
}

SongsInLibrarySortFilter::~SongsInLibrarySortFilter()
{

}

void SongsInLibrarySortFilter::setSelectionModel(QItemSelectionModel *selectionModel)
{
    this->selectionModel = selectionModel;
    connect(selectionModel,SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this,SLOT(selectionChanged(QItemSelection,QItemSelection)));
}

bool SongsInLibrarySortFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{

    QString pattern = filterRegExp().pattern();
    if(pattern.isEmpty()) {
        return true;
    } else {
        QRegExp regex;
        QString text;
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

bool SongsInLibrarySortFilter::checkText(int column, int sourceRow, const QModelIndex &sourceParent, QRegExp * regex) const
{
        static const QRegularExpression theRegex(QString("(the\\s)"),QRegularExpression::CaseInsensitiveOption);
        QString text = sourceModel()->data(sourceModel()->index(sourceRow, column, sourceParent)).toString();
        text.remove(theRegex);
        return text.contains(*regex);
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
