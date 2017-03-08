#ifndef PATHSCANNER_H
#define PATHSCANNER_H

#include <QStringList>
#include <QDir>
class PathScanner
{
public:
    PathScanner();
    QStringList & scanDirectory(const QString &directoryPath, const QStringList & filters, const bool rootLevelCall = true);
private:
    QStringList foundPaths;
};

#endif // PATHSCANNER_H
