#ifndef EXTRAFILTERS_H
#define SORTEDTAGVALUES_H
#include <QHash>
#include <QString>
#include <QStringList>
#include "songsinlibrary.h"
class SortedTagValues
{
public:
    SortedTagValues(SongsInLibrary * songsInLibrary);
    void refresh(QStringList & tagNames);
    void clear();
protected:
    QHash<QString,QStringList *> filters; //tagName, list of existing values of the tag in songsLibrary
private:
    SongsInLibrary * songsInLibrary;
};

#endif // SORTEDTAGVALUES_H
