#include "pathscanner.h"

PathScanner::PathScanner()
{

}

QStringList & PathScanner::scanDirectory(const QString &directoryPath, const QStringList & filters, const bool rootLevelCall)
{ 
    if(rootLevelCall) {
        foundPaths.clear();
    }
    QDir dir(directoryPath);
    if(dir.exists()) {
        if(!filters.isEmpty()) {
            dir.setNameFilters(filters);
        }
        dir.setFilter(QDir::Files | QDir::NoDotAndDotDot | QDir::NoSymLinks);
        QStringList filesList = dir.entryList();
        for(QString f : filesList) {
            foundPaths.append(dir.absolutePath() + "/" + f);
        }
        dir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
        QStringList dirList = dir.entryList();
        for(QString d : dirList) {
            scanDirectory(dir.absolutePath() + "/" +d, filters, false);
        }
    }
    return foundPaths;
}
