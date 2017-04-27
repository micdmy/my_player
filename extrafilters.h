#ifndef EXTRAFILTERS_H
#define EXTRAFILTERS_H
#include <QHash>
#include <QString>
#include <QStringList>
#include "songsinlibrary.h"
class ExtraFilters
{
public:
    ExtraFilters(SongsInLibrary * songsInLibrary);
    refresh(QStringList & tagNames);
private:
    SongsInLibrary * SongsInLibrary;
};

#endif // EXTRAFILTERS_H
