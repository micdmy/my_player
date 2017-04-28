#include "columnnames.h"

ColumnNames::ColumnNames()
{
    upToDate =false;
}

const QString &ColumnNames::getName(const int index) const
{
    return numberSortedData.at(index);
}

int ColumnNames::getIndex(const QString &name) const
{
    return textSortedData.value(name);
}

void ColumnNames::setData(QStringList names)
{
    numberSortedData = names;
    numberSortedToTextSorted();
}

void ColumnNames::appendData(QString name)
{
    numberSortedData.append(name);
    textSortedData.insert(name,numberSortedData.length() - 1);
}

void ColumnNames::clearData()
{
    textSortedData.clear();
    numberSortedData.clear();
}

void ColumnNames::setUpToDate(bool upToDate)
{
    this->upToDate = upToDate;
}

bool ColumnNames::isUpToDate() const
{
    return upToDate;
}

void ColumnNames::numberSortedToTextSorted()
{
    textSortedData.clear();
    for(int i=0; i<numberSortedData.length(); i++) {
        textSortedData.insert(numberSortedData.at(i), i);
    }
}
