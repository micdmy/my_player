#include "sortedtagvalues.h"

SortedTagValues::SortedTagValues(SongsInLibrary * songsInLibrary):
    songsInLibrary(songsInLibrary)
{

}
/*
 * Scans songsInLibrary, makes lists of different tag values
 * for each tagName in tagNames parameter.
 */
void SortedTagValues::refresh(QStringList &tagNames)
{
    clear();
    if(songsInLibrary != NULL) {
        for(QString tagName : tagNames) {
            QStringList * tagValues = new QStringList();
            songsInLibrary->findAllValuesOfTag(tagName,tagValues); //modifies tagValues
            filters.insert(tagName,tagValues);
        }
    }
}
/*
 * Removes all values of all tag names.
 */
void SortedTagValues::clear()
{
    filters.clear();
}


