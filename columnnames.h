#ifndef COLUMNNAMES_H
#define COLUMNNAMES_H
#include <QHash>

class ColumnNames
{
public:
    ColumnNames();
    const QString &getName(const int index) const;
    int  getIndex(const QString & name) const ;
    void setData(QStringList names);
    void appendData(QString name);
    void clearData();
    void setUpToDate(bool upToDate);
    bool isUpToDate() const;
private:
    QHash<QString, int> textSortedData;
    QStringList numberSortedData;
    void numberSortedToTextSorted();
    bool upToDate;
};

#endif // COLUMNNAMES_H
