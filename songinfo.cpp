#include "songinfo.h"

#define PATHKEY "Path"

/*
 * Static list of tags, which function readFile()
 * seeks in file.
 */

TagLib::StringList SongInfo::usedTags;
QStringList SongInfo::usedTagsQ;
QString SongInfo::emptyString;
SongInfo::SongInfo(QObject *parent):
QObject(parent)
{

}
/*
 * Constructs SongInfo reading tags from file at path.
 */
SongInfo::SongInfo(const QString & path)
{
    setPath(path);
    readFile();
}

SongInfo::SongInfo(const SongInfo &s)
{
    data = s.data;
}

SongInfo &SongInfo::operator =(const SongInfo &s)
{
    this->data = s.data;
    return *this;
}
/*
 * Returs tag described with key.
 * If such do not exists, returns empty QString
 */
QString SongInfo::getMetadata(const QString &key)
{
    return data.operator [](key);
}

QString & SongInfo::getMetadata(int column)
{
    return data.operator [](usedTagsQ.operator [](column));
}

/*
 * To be used with saving tags to files.
 * Doesn't work yet.
 */
void SongInfo::setMetadata(const QString &/*key*/, QString &/*value*/)
{
    //data.insert(key, value);
}

/*
 * Static function.
 * Sets new values to static member usedTags.
 * Those values are used to determine which tags
 * should be read from file.
 */
void SongInfo::setUsedTags(const QStringList &tags)
{
    usedTagsQ.clear();
    usedTagsQ << PATHKEY;
    usedTagsQ += tags;
    usedTags.clear();
    for(int i=0; i<tags.length();i++) {
        usedTags.append(TagLib::String(tags.at(i).toStdString()));
    }
}

int SongInfo::getUsedTagsCount()
{
    return usedTagsQ.length();
}

QString &SongInfo::getUsedTag(int index)
{
    if(index < usedTagsQ.length()) {
        return usedTagsQ.operator [](index);
    }
    return emptyString;
}


/*
 * Returns path of asociated file.
 */
QString SongInfo::getPath()
{
    return data.value(PATHKEY,QString());
}
/*
 * Sets path of file to work with.
 */
void SongInfo::setPath(const QString & path)
{
    data.insert(PATHKEY, path);
}
/*
 * Reads tags from file on path set with setPath(QString).
 * Reads only tags set with setUsedTags(cost QString &).
 * Saves tags in private member QHash<QString,QString> data.
 */
void SongInfo::readFile()
{
    clearDataExceptPath();
    //todo check if audioproperties realy neede
    TagLib::FileRef fileRef(getPath().toLatin1().data(),true,TagLib::AudioProperties::Accurate);
    if(!fileRef.isNull()) {
        for(TagLib::String tagName : usedTags) {
            data.insert(QString(tagName.toCString()),
                        QString(fileRef.               //get FileRef
                                tag()->                //get *Tag
                                properties().          //get PropertyMap
                                operator[](tagName).   //get StringList
                                toString().            //get String
                                toCString()));          //get *char in Latin1
        }
    } else {
        //todo handle error
    }
}

/*
 * Clear all tags saved in data, except path to file.
 */
void SongInfo::clearDataExceptPath()
{
    QString path = getPath();
    data.clear();
    setPath(path);
}

/*
 * Reading from stream.
 */
QDataStream & operator>>(QDataStream &dStream,  SongInfo & songInfo)
{
    songInfo.data.clear();
    dStream >> songInfo.data;
    return dStream;
}

/*
 * Saving to stream.
 */
QDataStream & operator<<(QDataStream & dStream, const SongInfo & songInfo)
{
    dStream << songInfo.data;
    return dStream;
}



