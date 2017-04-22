#include "onetagsortfilter.h"

OneTagSortFilter::OneTagSortFilter(QObject *parent):
    QSortFilterProxyModel(parent)
{

}

bool OneTagSortFilter::filterAcceptsRow(int sourceRow, const QModelIndex &sourceParent) const
{
     return checkfilter(sourceRow, sourceParent);
}

bool OneTagSortFilter::checkfilter(int sourceRow, const QModelIndex &sourceParent) const
{
    QString pattern = filterRegExp().pattern();
    if(pattern.isEmpty()) {
        return true;
    } else {
        QRegExp regex;
        /*
         * if pattern longer then 2 chars, searches in whole text,
         * otherwise matches only beginnig of the text
         */
        if(pattern.length() <= 2) {
            pattern.insert(0,"^");
        }
        regex.setPattern(pattern);
        regex.setCaseSensitivity(Qt::CaseInsensitive);

        return checkText(0 /*column nr 0*/, sourceRow, sourceParent, &regex);
    }
}

bool OneTagSortFilter::checkText(int column, int sourceRow, const QModelIndex &sourceParent, QRegExp *regex) const
{
    static const QRegularExpression theRegex(QString("(the\\s)"),QRegularExpression::CaseInsensitiveOption);
    QString text = sourceModel()->data(sourceModel()->index(sourceRow, column, sourceParent)).toString();
    text.remove(theRegex);
    return text.contains(*regex);
}