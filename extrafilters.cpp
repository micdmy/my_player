#include "extrafilters.h"

ExtraFilters::ExtraFilters(SongsInLibrary * songsInLibrary):
    songsInLibrary(songsInLibrary)
{

}

ExtraFilters::refresh(QStringList &tagNames)
{

}

ExtraFilters::clear()
{
    filters.clear();
}


